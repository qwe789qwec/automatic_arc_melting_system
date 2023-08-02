#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <iostream>
#include "main_process/sequence.hpp"

bool Init::check(deviceState devices){
    std::vector<Devices> deviceslist = 
    {   Devices::SLIDER1, 
        Devices::SLIDER2, 
        Devices::SLIDER3, 
        Devices::WEIGHING, 
        Devices::COBOTTA 
    };
    return devices.checkDevicesList(deviceslist, DeviceStatus::STANDBY);
}

std::vector<std::string> Init::process(){
    std::vector<std::string> action = {
        "slider1 init",
        "slider2 init",
        "slider3 init",
        "weighing init",
        "cobotta init"
    };
    return action;
}

bool Init::end(deviceState devices){
    std::vector<Devices> deviceslist = 
    {   Devices::SLIDER1, 
        Devices::SLIDER2, 
        Devices::SLIDER3, 
        Devices::WEIGHING, 
        Devices::COBOTTA 
    };
    return devices.checkDevicesList(deviceslist, DeviceStatus::STANDBY);
}