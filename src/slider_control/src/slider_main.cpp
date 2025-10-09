#include <cstdlib>
#include "ros2_utils/instrument_node.hpp"
#include "slider_control/slider.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    auto slider_control = std::make_unique<slider>("192.168.0.3", 64511);
    
    // create instrument node
    auto node = std::make_shared<InstrumentNode>(
        "slider",
        std::move(slider_control),
        "Process_service",
        "topic"
    );

    // test action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        node->test_instrument_action(argv[1]);
        test = false;
    }

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}