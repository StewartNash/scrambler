#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"

class Animator : public rclcpp::Node {
	public:
		Animator() : Node("animator") {
			publisher_ = this->create_publisher<std_msgs::msg::Int16MultiArray>("animations", 1);
		}

		void publishAnimation(const std::vector<int16_t>& data) {
			auto message = std_msgs::msg::Int16MultiArray();
			message.data = data;
			//RCLCPP_INFO(this->get_logger(), "Publishing Int16MultiArray with %zu elements.", data.size());
			publisher_->publish(message);
		}

	private:
		rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
};

int main(int argc, char* argv[]) {
	rclcpp::init(argc, argv);
	auto node = std::make_shared<Animator>();

	std::vector<int16_t> sampleData = {1, 2, 3, 4, 5};
	node->publishAnimation(sampleData);

	rclcpp::spin_some(node);
	rclcpp::shutdown();

	return 0;
}
