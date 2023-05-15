#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

class state
{
public:
	state();
    std::string slider(std::string action);
    std::string weighing(std::string action);
    std::string cobotta(std::string action);
    std::string PLC(std::string action);
    ~state();

private:
};

#endif // RECTANGLE_HPP