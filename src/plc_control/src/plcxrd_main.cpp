#include <cstdlib>
#include "plc_control/plcxrd_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test plc action  omitted, 20250619 to test
    // bool test = false;
    // if (argc == 2 && test) {
    //     RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
    //     PlcSystem::test_plc_action(argv[1]);
    //     test = false;
    // }
    
    // create node
    auto node = std::make_shared<PlcxrdSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}