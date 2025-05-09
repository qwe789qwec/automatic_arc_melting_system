#ifndef DEVICES_STATE_HPP
#define DEVICES_STATE_HPP

#include <string>
#include <vector>
#include <map>
#include <memory>

enum class Situation {
    ONLINE,
    OFFLINE,
    ACTION,
    STANDBY,
    ERROR
};

class Device {
public:
    Device(const std::string& id);
    
    std::string getId() const { return id_; }
    void setStatus(Situation status);
    Situation getStatus() const { return status_; }
    
    void addComponent(const std::string& component_id);
    bool hasComponent(const std::string& component_id) const;
    void setComponentStatus(const std::string& component_id, Situation status);
    Situation getComponentStatus(const std::string& component_id) const;
    
    bool isAllInStatus(Situation status) const;

private:
    std::string id_;
    Situation status_;
    std::map<std::string, Situation> components_;
};

class DeviceStateManager {
public:
    DeviceStateManager();
    
    bool addDevice(const std::string& device_id);
    bool hasDevice(const std::string& device_id) const;
    bool removeDevice(const std::string& device_id);
    
    bool addComponent(const std::string& device_id, const std::string& component_id);
    
    Situation getDeviceStatus(const std::string& device_id) const;
    bool updateDeviceStatus(const std::string& message);
    
    bool checkDevices(Situation status) const;
    bool checkDevicesList(const std::vector<std::string>& devicesList, Situation status) const;

    bool initializing;
    
private:
    std::map<std::string, std::shared_ptr<Device>> devices_;
};

#endif // DEVICES_STATE_HPP
