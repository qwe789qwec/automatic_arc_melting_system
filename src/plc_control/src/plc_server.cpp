#include "rclcpp/rclcpp.hpp"
#include "msg_format/srv/plc_format.hpp"
#include "tcp_handle/tcp_socket.hpp"

#include <memory>

void plc_main(const std::shared_ptr<msg_format::srv::PlcFormat::Request> request,
          std::shared_ptr<msg_format::srv::PlcFormat::Response>      response)
{   
    std::string action = request->action;
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "action: %s", action.c_str());

    std::string plc_ip = "192.168.0.4";
    int plc_port = 9527;
    tcp_socket plc_handler(plc_ip, plc_port);
    plc_handler.create();
    plc_handler.write(action);
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
