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
   Devices name;
   DeviceStatus status;
};

enum class DeviceStatus {
   ONLINE,
   OFFLINE,
   ACTION,
   STANDBY,
   ERROR
};

enum class Devices {
   SLIDER1,
   SLIDER2,
   SLIDER3,
   WEIGHING,
   COBOTTA
};

class deviceState
{
    public:
        void addDevice(Devices device);
        void removeDevice(Devices device);
        DeviceStatus getDeviceStatus(Devices device);
        Devices stringToDevice(std::string device);
        bool checkDevices(DeviceStatus status);
        bool checkDevicesList(std::vector<Devices> deviceslist, DeviceStatus status);
        void updateDeviceStatus(std::string message);
    private:
        std::vector<Device> devices;
};

#endif // RECTANGLE_HPP