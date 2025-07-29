#include <cstdlib>
#include "cppblank/instrument_node.hpp"

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    
    // test plc action
    bool test = false;
    if (argc == 2 && test) {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Start test");
        InstrumentSystem::test_insturment_action(argv[1]);
        test = false;
    }
    
    // create node
    auto node = std::make_shared<InstrumentSystem>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}