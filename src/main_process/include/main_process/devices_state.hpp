#ifndef SLIDER_HPP
#define SLIDER_HPP

#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string>
#include <vector>

enum class Situation {
   ONLINE,
   OFFLINE,
   ACTION,
   STANDBY,
   ERROR
};

enum class Instrument {
   SLIDER,
   SLIDER1,
   SLIDER2,
   SLIDER3,
   WEIGHING,
   COBOTTA,
   PLC,
   error
};

struct Device {
   Instrument name;
   Situation status;
};

class deviceState
{
    public:
        deviceState();
        bool initialized;
        void addDevice(Instrument device);
        void removeDevice(Instrument device);
        Situation getDeviceStatus(Instrument device);
        Instrument stringToDevice(std::string device);
        bool checkDevices(Situation status);
        bool checkDevicesList(std::vector<Instrument> deviceslist, Situation status);
        void updateDeviceStatus(std::string message);
    private:
        std::vector<Device> devices;
};

#endif // RECTANGLE_HPP