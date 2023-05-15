#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "main_process/devices_state.hpp"

void state::addDevice(std::string device){
	// add the device to the list
	Device newDevice;
	newDevice.name = device;
	newDevice.status = DeviceStatus::STANDBY;
	devices.push_back(newDevice);
}
void state::removeDevice(std::string device){
	// remove the device from the list
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name.compare(device) == 0){
			devices.erase(devices.begin() + i);
		}
	}
}
DeviceStatus state::getDeviceStatus(std::string device){
	// return the status of the device
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name.compare(device) == 0){
			return devices[i].status;
		}
	}
	return DeviceStatus::ERROR;
}
bool state::checkDevices(){
	// if all devices are standby, return true
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].status != DeviceStatus::STANDBY){
			return false;
		}
	}
	return true;
}

void state::updateDeviceStatus(std::string message){
	// update the status of the device
	std::string device = message.substr(0, message.find(" "));
	std::string status = message.substr(message.find(" ") + 1, message.length());
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name.compare(device) == 0){
			if (status.compare("online") == 0){
				devices[i].status = DeviceStatus::ONLINE;
			}
			else if (status.compare("offline") == 0){
				devices[i].status = DeviceStatus::OFFLINE;
			}
			else if (status.compare("action") == 0){
				devices[i].status = DeviceStatus::ACTION;
			}
			else if (status.compare("standby") == 0){
				devices[i].status = DeviceStatus::STANDBY;
			}
			else if (status.compare("error") == 0){
				devices[i].status = DeviceStatus::ERROR;
			}
		}
	}
}