#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "main_process/devices_state.hpp"

void deviceState::addDevice(Devices device){
	// add the device to the list
	Device newDevice;
	newDevice.name = device;
	newDevice.status = DeviceStatus::STANDBY;
	devices.push_back(newDevice);
}

void deviceState::removeDevice(Devices device){
	// remove the device from the list
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name == device){
			devices.erase(devices.begin() + i);
		}
	}
}

DeviceStatus deviceState::getDeviceStatus(Devices device){
	// return the status of the device
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name == device){
			return devices[i].status;
		}
	}
	return DeviceStatus::ERROR;
}

Devices deviceState::stringToDevice(std::string device){
	// convert string to device
	if (device.compare("slider1") == 0){
		return Devices::SLIDER1;
	}
	else if (device.compare("slider2") == 0){
		return Devices::SLIDER2;
	}
	else if (device.compare("slider3") == 0){
		return Devices::SLIDER3;
	}
	else if (device.compare("weighing") == 0){
		return Devices::WEIGHING;
	}
	else if (device.compare("cobotta") == 0){
		return Devices::COBOTTA;
	}
	else{
		return Devices::SLIDER1;
	}
}

bool deviceState::checkDevices(DeviceStatus status){
	// if all devices are standby, return true
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].status != status){
			return false;
		}
	}
	return true;
}

bool deviceState::checkDevicesList(std::vector<Devices> devicesList, DeviceStatus status){
	// check if all device on the devicesList in the devices are standby
	// if all devices are standby, return true
	for (int i = 0; i < devicesList.size(); i++){
		for (int j = 0; j < devices.size(); j++){
			if (devices[j].name == devicesList[i]){
				if (devices[j].status != status){
					return false;
				}
			}
		}
	}
	return true;
}

void deviceState::updateDeviceStatus(std::string message){
	// update the status of the device
	std::string device = message.substr(0, message.find(" "));
	Devices deviceEnum = stringToDevice(device);
	std::string status = message.substr(message.find(" ") + 1, message.length());
	for (int i = 0; i < devices.size(); i++){
		if (devices[i].name == deviceEnum){
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