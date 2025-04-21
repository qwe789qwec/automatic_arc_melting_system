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
    initialized = false;
}

void DeviceStateManager::addDevice(const std::string& device_id) {
    if (devices_.find(device_id) == devices_.end()) {
        devices_[device_id] = std::make_shared<Device>(device_id);
    }
}

void DeviceStateManager::removeDevice(const std::string& device_id) {
    devices_.erase(device_id);
}

bool DeviceStateManager::hasDevice(const std::string& device_id) const {
    return devices_.find(device_id) != devices_.end();
}

void DeviceStateManager::addComponent(const std::string& device_id, const std::string& component_id) {
    if (hasDevice(device_id)) {
        devices_[device_id]->addComponent(component_id);
    }
}

Situation DeviceStateManager::getDeviceStatus(const std::string& device_id) const {
    auto it = devices_.find(device_id);
    if (it != devices_.end()) {
        const auto& [id, device] = *it;
		const auto& status = device->getStatus();
        return status;
    }
    return Situation::ERROR;
}

void DeviceStateManager::updateDeviceStatus(const std::string& message) {
    std::istringstream iss(message);
    std::string device_id, status_str;
    std::string component_id;
    
    iss >> device_id;
    
    std::string next;
    while (iss >> next) {
        if (next == "online" || next == "offline" || next == "action" || 
            next == "standby" || next == "error") {
            status_str = next;
            break;
        } else {
            if (component_id.empty()) {
                component_id = next;
            } else {
                component_id += " " + next;
            }
        }
    }
    
    if (status_str.empty() && !component_id.empty()) {
        size_t last_space = component_id.find_last_of(' ');
        if (last_space != std::string::npos) {
            status_str = component_id.substr(last_space + 1);
            component_id = component_id.substr(0, last_space);
        } else {
            status_str = component_id;
            component_id = "";
        }
    }
    
    Situation status = Situation::ERROR;
    if (status_str == "online") status = Situation::ONLINE;
    else if (status_str == "offline") status = Situation::OFFLINE;
    else if (status_str == "action") status = Situation::ACTION;
    else if (status_str == "standby") status = Situation::STANDBY;
    
    if (hasDevice(device_id)) {
        if (component_id.empty()) {
            devices_[device_id]->setStatus(status);
        } else {
            if (!devices_[device_id]->hasComponent(component_id)) {
                devices_[device_id]->addComponent(component_id);
            }
            devices_[device_id]->setComponentStatus(component_id, status);
        }
    } else {
        addDevice(device_id);
        devices_[device_id]->setStatus(status);
        
        if (!component_id.empty()) {
            devices_[device_id]->addComponent(component_id);
            devices_[device_id]->setComponentStatus(component_id, status);
        }
    }
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