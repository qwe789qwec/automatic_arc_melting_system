#include <cstdlib>
#include "weighing_control/weighing_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test weighing machine
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        WeighingSystem::test_weighing_machine(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<WeighingSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}