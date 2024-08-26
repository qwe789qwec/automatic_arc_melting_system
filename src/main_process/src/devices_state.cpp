#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>
#include <vector>

#include "main_process/devices_state.hpp"

deviceState::deviceState(){
	// initialize the device state
	initialized = false;
}

void deviceState::addDevice(Instrument device){
	// add the device to the list
	if(initialized == false){
		Device newDevice;
		newDevice.name = device;
		newDevice.status = Situation::ACTION;
		devices.push_back(newDevice);
	}
}

void deviceState::removeDevice(Instrument device){
	// remove the device from the list
	long unsigned int i;
	for (i = 0; i < devices.size(); i++){
		if (devices[i].name == device){
			devices.erase(devices.begin() + i);
		}
	}
}

Situation deviceState::getDeviceStatus(Instrument device){
	// return the status of the device
	long unsigned int i;
	for (i = 0; i < devices.size(); i++){
		if (devices[i].name == device){
			return devices[i].status;
		}
	}
	return Situation::ERROR;
}

Instrument deviceState::stringToDevice(std::string device){
	// convert string to device
	if (device.compare("slider") == 0){
		return Instrument::SLIDER;
	}
	else if (device.compare("slider1") == 0){
		return Instrument::SLIDER1;
	}
	else if (device.compare("slider2") == 0){
		return Instrument::SLIDER2;
	}
	else if (device.compare("slider3") == 0){
		return Instrument::SLIDER3;
	}
	else if (device.compare("weighing") == 0){
		return Instrument::WEIGHING;
	}
	else if (device.compare("cobotta") == 0){
		return Instrument::COBOTTA;
	}
	else if (device.compare("plc") == 0){
		return Instrument::PLC;
	}
	else{
		return Instrument::error;
	}
}

bool deviceState::checkDevices(Situation status){
	// if all devices are standby, return true
	long unsigned int i;
	for (i = 0; i < devices.size(); i++){
		printf("count:%ld \n", i);
		if (devices[i].status != status){
			printf("false\n");
			return false;
		}
	}
	printf("all true\n");
	return true;
}

bool deviceState::checkDevicesList(std::vector<Instrument> devicesList, Situation status){
	// check if all device on the devicesList in the devices are standby
	// if all devices are standby, return true
	long unsigned int i,j;
	for (i = 0; i < devicesList.size(); i++){
		for (j = 0; j < devices.size(); j++){
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
	Instrument deviceEnum = stringToDevice(device);
	if(deviceEnum == Instrument::error){
		return;
	}
	std::string status = message.substr(message.find(" ") + 1, message.length());
	long unsigned int i;
	for (i = 0; i < devices.size(); i++){
		if (devices[i].name == deviceEnum){
			if (status.compare("online") == 0){
				devices[i].status = Situation::ONLINE;
			}
			else if (status.compare("offline") == 0){
				devices[i].status = Situation::OFFLINE;
			}
			else if (status.compare("action") == 0){
				devices[i].status = Situation::ACTION;
			}
			else if (status.compare("standby") == 0){
				devices[i].status = Situation::STANDBY;
			}
			else if (status.compare("error") == 0){
				devices[i].status = Situation::ERROR;
			}
		}
	}
}