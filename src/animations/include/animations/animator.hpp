#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int16_multi_array.hpp"

namespace scrambler {

class Animator : public rclcpp::Node {
	public:
		Animator();
		void publishAnimation(const std::vector<int16_t>& data);

	private:
		rclcpp::Publisher<std_msgs::msg::Int16MultiArray>::SharedPtr publisher_;
};

} /* namespace scrambler */
