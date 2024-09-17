#include <chrono>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class KeyboardPublisher : public rclcpp::Node
{
public:
  KeyboardPublisher()
  : Node("keyboard_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("keyboard_data", 10);
    auto timer_callback =
      [this]() -> void {
        std::string input;
        std::getline(std::cin, input);

        auto message = std_msgs::msg::String();
        message.data = std::to_string(this->count_++) + " >> " + input;
          
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        this->publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(100ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<KeyboardPublisher>());
  rclcpp::shutdown();
  return 0;
}
