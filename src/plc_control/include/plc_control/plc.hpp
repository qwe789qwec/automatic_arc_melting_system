#ifndef PLC_HPP
#define PLC_HPP

#include <string>
#include <vector>
#include "tcp_handle/tcp_socket.hpp"

class plc
{
public:
    plc(std::string ip, int port);
    ~plc();
    bool make_action(std::string step);

private:
    // Modbus function codes
    static constexpr const char* READ_COIL = "\x01";
    static constexpr const char* READ_INPUT = "\x02";
    static constexpr const char* READ_REGISTER = "\x03";
    static constexpr const char* WRITE_COIL = "\x05";
    static constexpr const char* WRITE_REGISTER = "\x06";
    
    // Coil states
    static constexpr const char* COIL_ON = "\xFF\x00";
    static constexpr const char* COIL_OFF = "\x00\x00";
    
    // PLC Input addresses
    static constexpr const char* EMGX3 = "\x00\x03";
    static constexpr const char* WATER_LEAK_X4 = "\x00\x04";
    static constexpr const char* WATER_FLOW_X5 = "\x00\x05";
    static constexpr const char* PRESURE_50_X6 = "\x00\x06";
    static constexpr const char* PRESURE_90_X7 = "\x00\x07";
    
    // PLC Output addresses
    static constexpr const char* WATER_Y4 = "\x00\x04";
    static constexpr const char* AIR_FLOW_Y12 = "\x00\x0A";
    static constexpr const char* BUZZ_Y17 = "\x00\x17";
    
    // PLC Register addresses
    static constexpr const char* PUMP_M10 = "\x20\x0A";
    static constexpr const char* SPUMP_M11 = "\x20\x0B";
    static constexpr const char* VENT_M15 = "\x20\x0F";
    static constexpr const char* OPEN_GATE_VALVE_M17 = "\x20\x11";
    static constexpr const char* CLOSE_GATE_VALVE_M19 = "\x20\x13";
    static constexpr const char* ARC_ON_M20 = "\x20\x14";
    static constexpr const char* ARC_OFF_M21 = "\x20\x15";
    static constexpr const char* FLIP_M30 = "\x20\x1E";
    static constexpr const char* FLIP_S33 = "\xB0\x21";
    
    static constexpr const char* PRESURE_S12 = "\xB0\x0C";
    static constexpr const char* S13_COIL = "\xB0\x0D";
    static constexpr const char* S14_COIL = "\xB0\x0E";
    static constexpr const char* S16_COIL = "\xB0\x10";
    
    static constexpr const char* SD6180 = "\x68\x24";  // For analog

    char* modbus(const char* function, const char* component, const char* data);
    char* dec2hex(int value);
    char* writeRaw(const void* input, int &size);
    char* coilWrite(const char* component, const char* data);
    bool coilRead(const char* component);
    bool inputRead(const char* component);
    char* registerWrite(const char* component, int data);
    bool registerRead(const char* component, int data);
    
    // TCP socket for communication
    tcp_socket plc_tcp;
};

#endif // PLC_HPP