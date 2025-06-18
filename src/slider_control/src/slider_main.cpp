#include <cstdlib>
#include "slider_control/slider_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test slider action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        SliderSystem::test_slider_action(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<SliderSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}