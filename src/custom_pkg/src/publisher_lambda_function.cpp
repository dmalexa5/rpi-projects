// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses a fancy C++11 lambda
 * function to shorten the callback syntax, at the expense of making the
 * code somewhat more difficult to understand at first glance. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
    auto timer_callback =
      [this]() -> void {
        
        std::string user_input;
        std::cout << ">>> ";
        std::getline(std::cin, user_input);
        /*int value;
        
        value = get_valid_num(user_input);
        
        if (value == -1) {
          std::cout << "Please enter a value between 0 and 180 \n";
          return;
        }
        */
        auto message = std_msgs::msg::String();
        // user_input = std::to_string(value);
        
        message.data =  user_input; //+ "  at count: " + std::to_string(this->count_++);
        RCLCPP_INFO(this->get_logger(), "%s", message.data.c_str());
        this->publisher_->publish(message);
      };
    timer_ = this->create_wall_timer(100ms, timer_callback);
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
  size_t count_;
  
  int get_valid_num(std::string str) {
    //
    // Coded with ChatGPT 4o mini
    //
    
    if (str.empty()) {
      return -1;
    }
    
    // Convert string to int
    char *end;
    long value = std::strtol(str.c_str(), &end, 10);
    
    // Check if the entire string was converted and the conversion was valid
    if (*end != '\0' || value < 0 || value > 180 || value > std::numeric_limits<int>::max()) {
      return -1;
    }

    return value;
  }
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
