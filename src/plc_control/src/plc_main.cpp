#include <cstdlib>
#include "ros2_utils/instrument_node.hpp"
#include "plc_control/plc.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    auto plc_control = std::make_unique<plc>("192.168.0.5", 9528);

    // create instrument node
    auto node = std::make_shared<InstrumentNode>(
        "plc",
        std::move(plc_control),
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