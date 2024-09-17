#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <iostream>

class KeyboardSubscriber : public rclcpp::Node
{
public:
    KeyboardSubscriber()
    : Node("keyboard_subscriber")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "keyboard_data", 10, [this](std_msgs::msg::String::UniquePtr msg) {
                RCLCPP_INFO(this->get_logger(), "Received: '%s'", msg->data.c_str());
            });
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<KeyboardSubscriber>());
    rclcpp::shutdown();
    return 0;
}
