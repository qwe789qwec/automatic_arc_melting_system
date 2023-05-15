#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define slider1 0
#define slider2 1
#define slider3 2
#define weighing 3
#define cobotta 4

class state
{
    public:
        void addDevice(std::string device);
        void removeDevice(std::string device);
        bool getDeviceStatus(std::string device);
        void updateDeviceStatus(std::string device, bool status);
    private:
        std::vector<std::string> devices;
};

#endif // RECTANGLE_HPP