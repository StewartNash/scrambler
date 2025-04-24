#include "animations/animator.hpp"

using namespace scrambler;

Animator::Animator() : rclcpp::Node("animator") {
			publisher_ = this->create_publisher<std_msgs::msg::Int16MultiArray>("animations", 1);
}

void Animator::publishAnimation(const std::vector<int16_t>& data) {
			auto message = std_msgs::msg::Int16MultiArray();
			message.data = data;
			//RCLCPP_INFO(this->get_logger(), "Publishing Int16MultiArray with %zu elements.", data.size());
			publisher_->publish(message);
}

