#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class KeyboardSubscriber : public rclcpp::Node
{
public:
  KeyboardSubscriber()
  : Node("keyboard_subscriber")
  {
    auto keyboard_data_callback =
      [this](std_msgs::msg::String::UniquePtr msg) -> void {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
      };
    subscription_ =
      this->create_subscription<std_msgs::msg::String>("keyboard_data", 10, keyboard_data_callback);
  }

private:
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<KeyboardSubscriber>());
  rclcpp::shutdown();
  return 0;
}
