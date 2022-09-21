#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/plc_format.hpp"
#include "plc_control/plc_socket.hpp"

#include <memory>

void plc_main(const std::shared_ptr<msg_format::srv::PlcFormat::Request> request,
          std::shared_ptr<msg_format::srv::PlcFormat::Response>      response)
{   
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

    std::string plc_ip = "172.17.4.71";
    int plc_port = 35353;
    plc_socket plc_handler(plc_ip, plc_port);
    plc_handler.create();
    char* write_msg = strcpy(new char[action.length() + 1], action.c_str());
    plc_handler.write(write_msg);
    char receive_msg[1024] = "init msg";
    plc_handler.receive(receive_msg);
    plc_handler.end();
    response->result = receive_msg;
    return;
}

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("plc_server");

    rclcpp::Service<msg_format::srv::PlcFormat>::SharedPtr PlcServer =
        node->create_service<msg_format::srv::PlcFormat>("plc_format", &plc_main);

    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "plc_main");

    rclcpp::spin(node);
    rclcpp::shutdown();
}
