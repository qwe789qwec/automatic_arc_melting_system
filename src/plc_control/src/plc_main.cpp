#include <cstdlib>
#include "plc_control/plc_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test plc action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        PlcSystem::test_plc_action(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<PlcSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}