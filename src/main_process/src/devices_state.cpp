#include <chrono>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <iostream>
#include <sstream>
#include "main_process/devices_state.hpp"

// Device
Device::Device(const std::string& id) 
    : id_(id), status_(Situation::STANDBY) {
}

void Device::setStatus(Situation status) {
    status_ = status;
}

void Device::addComponent(const std::string& component_id) {
    if (components_.find(component_id) == components_.end()) {
        components_[component_id] = Situation::STANDBY;
    }
}

bool Device::hasComponent(const std::string& component_id) const {
    return components_.find(component_id) != components_.end();
}

void Device::setComponentStatus(const std::string& component_id, Situation status) {
    if (hasComponent(component_id)) {
        components_[component_id] = status;
    }
}

Situation Device::getComponentStatus(const std::string& component_id) const {
    auto it = components_.find(component_id);
    if (it != components_.end()) {
        const auto& [comp_id, status] = *it;
        return status;
    }
    return Situation::ERROR;
}

bool Device::isAllInStatus(Situation status) const {
    if (status_ != status) return false;
    
    for (const auto& [comp_id, comp_status] : components_) {
        if (comp_status != status) {
            return false;
        }
    }
    return true;
}

// DeviceStateManager
DeviceStateManager::DeviceStateManager() {
    initializing = false;
}

bool DeviceStateManager::addDevice(const std::string& device_id) {
    if (!initializing) {
        return false;
    }
    
    if (devices_.find(device_id) == devices_.end()) {
        devices_[device_id] = std::make_shared<Device>(device_id);
    }
    return true;
}

bool DeviceStateManager::removeDevice(const std::string& device_id) {
    if (!initializing) {
        return false;
    }
    
    auto it = devices_.find(device_id);
    if (it != devices_.end()) {
        devices_.erase(it);
        return true;
    }
    return false;
}

bool DeviceStateManager::hasDevice(const std::string& device_id) const {
    return devices_.find(device_id) != devices_.end();
}

bool DeviceStateManager::addComponent(const std::string& device_id, const std::string& component_id) {
    if (!initializing) {
        return false;
    }
    
    if (hasDevice(device_id)) {
        devices_[device_id]->addComponent(component_id);
        return true;
    }
    return false;
}

Situation DeviceStateManager::getDeviceStatus(const std::string& command) const {
    auto it = devices_.find(command);
    if (it != devices_.end()) {
        const auto& [id, device] = *it;
        const auto& status = device->getStatus();
        return status;
    }

	size_t first_underscore = command.find('_');
	std::string device_id, component_id;
    if (first_underscore != std::string::npos) {
		device_id = command.substr(0, first_underscore);
        component_id = command.substr(first_underscore + 1);
    }
	else {
		device_id = command;
		auto it = devices_.find(device_id);
		if (it == devices_.end()) {
			return Situation::ERROR;
		}
		const auto& [id, device] = *it;
		const auto& status = device->getStatus();
		return status;
	}

	auto it = devices_.find(device_id);
	if (it != devices_.end()) {
		const auto& [id, device] = *it;
		const auto& status = device->getComponentStatus(component_id);
		return status;
	}

    return Situation::ERROR;
}

bool DeviceStateManager::updateDeviceStatus(const std::string& message) {   
    std::string device_id;
    std::string component_id;
    std::string status_str;
    
    size_t first_underscore = message.find('_');
    if (first_underscore == std::string::npos) {
        // format error
        printf("Format error: missing underscore separator\n");
        return false;
    }
    
    device_id = message.substr(0, first_underscore);
    
    // find the second underscore
    size_t second_underscore = message.find('_', first_underscore + 1);
    if (second_underscore == std::string::npos) {
        // deviceId_statusStr
        status_str = message.substr(first_underscore + 1);
    } else {
        // deviceId_componentId_statusStr
        component_id = message.substr(first_underscore + 1, second_underscore - first_underscore - 1);
        status_str = message.substr(second_underscore + 1);
    }
    
    // set status
    Situation status = Situation::ERROR;
    if (status_str == "online") status = Situation::ONLINE;
    else if (status_str == "offline") status = Situation::OFFLINE;
    else if (status_str == "action") status = Situation::ACTION;
    else if (status_str == "standby") status = Situation::STANDBY;
    else {
        printf("Invalid status string: %s\n", status_str.c_str());
        return false;
    }
    
    // update device status
    if (hasDevice(device_id)) {
        if (component_id.empty()) {
            devices_[device_id]->setStatus(status);
        } else {
            if (!devices_[device_id]->hasComponent(component_id)) {
                return false; // component not found
            }
            devices_[device_id]->setComponentStatus(component_id, status);
        }
    } else {
        return false; // device not found
    }
    
    return true; // update success
}

bool DeviceStateManager::checkDevices(Situation status) const {
    if (devices_.empty()) return false;
    
    for (const auto& [device_id, device_ptr] : devices_) {  // 結構化綁定
        if (device_ptr->getStatus() != status) {
            printf("Device %s is not in %d status\n", 
                   device_id.c_str(), static_cast<int>(status));
            return false;
        }
    }
    
    printf("All devices in %d status\n", static_cast<int>(status));
    return true;
}

bool DeviceStateManager::checkDevicesList(const std::vector<std::string>& devicesList, Situation status) const {
    for (const auto& device_id : devicesList) {
        auto it = devices_.find(device_id);
        if (it == devices_.end()) {
            printf("Device %s not found\n", device_id.c_str());
            return false;
        }
        const auto& [id, device_ptr] = *it;
        if (device_ptr->getStatus() != status) {
            printf("Device %s is not in %d status\n", 
                   device_id.c_str(), static_cast<int>(status));
            return false;
        }
    }
    return true;
}