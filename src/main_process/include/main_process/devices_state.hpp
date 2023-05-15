#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <vector>

struct Device {
   std::string name;
   DeviceStatus status;
};

enum class DeviceStatus {
   ONLINE,
   OFFLINE,
   ACTION,
   STANDBY,
   ERROR
};

class state
{
    public:
        void addDevice(std::string device);
        void removeDevice(std::string device);
        DeviceStatus getDeviceStatus(std::string device);
        bool checkDevices();
        void updateDeviceStatus(std::string message);
    private:
        std::vector<Device> devices;
};

#endif // RECTANGLE_HPP