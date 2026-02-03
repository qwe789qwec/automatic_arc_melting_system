#ifndef INSTRUMENT_HPP
#define INSTRUMENT_HPP

#include <string>
#include <vector>
#include "tcp_handle/tcp_socket.hpp"

class instrumentc
{
public:
    instrumentc(std::string ip, int port);
    ~instrumentc();
    bool make_action(std::string step);

private:
    // define function codes
    static constexpr const char* NO_1 = "\x01";
    static constexpr const char* NO_2 = "\x02";
    static constexpr const char* NO_3 = "\x03";
    static constexpr const int number_ZERO = 0;
    static constexpr const int number_ONE = 1;
    static constexpr const int number_TWO = 2;

    bool initProcess();
    char* dec2hex(int value);
    
    // TCP socket for communication
    tcp_socket instrumentc_tcp;
};

#endif // INSTRUMENT_HPP