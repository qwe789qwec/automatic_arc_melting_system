#include <cstdlib>
#include "ros2_utils/instrument_node.hpp"
#include "weighing_control/weighing_machine.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    auto weighing_control = std::make_unique<weighing_machine>("192.168.0.2", 8001);

    // create instrument node
    auto node = std::make_shared<InstrumentNode>(
        "weighing",
        std::move(weighing_control),
        "process_service",
        "topic"
    );

    // test weighing machine
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