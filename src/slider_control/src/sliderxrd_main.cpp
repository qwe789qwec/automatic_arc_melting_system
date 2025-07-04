#include <cstdlib>
#include "slider_control/sliderxrd_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test slider action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        SliderxrdSystem::test_slider_action(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<SliderxrdSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}