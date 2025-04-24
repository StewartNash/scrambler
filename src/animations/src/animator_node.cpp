#include "animations/animator.hpp"

using namespace scrambler;

/*
int main(int argc, char* argv[]) {
	rclcpp::init(argc, argv);
	auto node = std::make_shared<Animator>();

	std::vector<int16_t> sampleData = {1, 2, 3, 4, 5};
	node->publishAnimation(sampleData);

	rclcpp::spin_some(node);
	rclcpp::shutdown();

	return 0;
}
*/

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
	auto node = std::make_shared<Animator>();
	
	rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}
