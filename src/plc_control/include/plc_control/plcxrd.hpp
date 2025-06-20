#ifndef PLCXRD_HPP
#define PLCXRD_HPP

#include <string>
#include <vector>
#include "tcp_handle/tcp_socket.hpp"

class plcxrd
{
public:
    plcxrd(std::string ip, int port);
    ~plcxrd();
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
    
    // PLC Output addresses
    
    // PLC Register addresses
    static constexpr const char* DOORLOCK_OPEN_M11  = "\x20\x0B"; // M11
    static constexpr const char* DOORLOCK_CLOSE_M12 = "\x20\x0C"; // M12
    static constexpr const char* DOOR_OPEN_M13      = "\x20\x0D"; // M13
    static constexpr const char* DOOR_CLOSE_M14     = "\x20\x0E"; // M14
    
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
    tcp_socket plcxrd_tcp;
};

#endif // PLCXRD_HPP