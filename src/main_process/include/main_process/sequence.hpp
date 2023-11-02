#include <chrono>
#include <cstdlib>
#include <memory>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <vector>

#include <iostream>
#include "devices_state.hpp"

class SequenceState {
public:
    virtual bool check(deviceState devices) = 0;
    virtual std::vector<std::string> process() = 0;
    virtual bool end(deviceState devices) = 0;
};

class Init : public SequenceState {
public:
    bool check(deviceState devices) override ;
    std::vector<std::string> process() override ;
    bool end(deviceState devices) override ;
};

class OutDosingHead : public SequenceState {
public:
    bool check(deviceState devices) override ;
    std::vector<std::string> process() override ;
    bool end(deviceState devices) override ;
};

class InDosingHead : public SequenceState {
public:
    bool check(deviceState devices) override ;
    std::vector<std::string> process() override ;
    bool end(deviceState devices) override ;
};

class Sequence {

public:
    deviceState devices;
    SequenceState* state;

    Sequence() {
        devices.addDevice(Devices::SLIDER1);
        devices.addDevice(Devices::SLIDER2);
        devices.addDevice(Devices::SLIDER3);
        devices.addDevice(Devices::WEIGHING);
        devices.addDevice(Devices::COBOTTA);

        state = new Init();
    }

    void setState(SequenceState* newState) {
        delete state;
        state = newState;
    }

    void end() {
        state->end(devices);
    }
};