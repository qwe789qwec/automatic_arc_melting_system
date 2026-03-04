#include <cstdlib>
#include "template_c/instrumentc_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test plc action
    bool test = false;
    auto node = std::make_shared<InstrumentCSystem>();
    
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        node->test_instrumentc_action(argv[1]);
        test = false;
    }
    
    // create node
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}