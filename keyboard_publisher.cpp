#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>
#include <string>

using namespace std::chrono_literals;

class KeyboardPublisher : public rclcpp::Node
{
public:
    KeyboardPublisher()
    : Node("keyboard_publisher")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("keyboard_data", 10);
        timer_ = this->create_wall_timer(
            100ms, [this]() { publish_keyboard_data(); });
    }

private:
    void publish_keyboard_data()
    {
        std::string input;
        std::getline(std::cin, input);

        auto message = std_msgs::msg::String();
        message.data = input;
        publisher_->publish(message);

        RCLCPP_INFO(this->get_logger(), "Published: '%s'", message.data.c_str());
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<KeyboardPublisher>());
    rclcpp::shutdown();
    return 0;
}
