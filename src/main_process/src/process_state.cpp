#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "main_process/process_state.hpp"



void state::addDevice(std::string device);
void state::removeDevice(std::string device);
bool state::getDeviceStatus(std::string device);
void state::updateDeviceStatus(std::string device, bool status);


// make array with 3 elements


state::state()
{
	static bool slider1 = false;
	static bool slider2 = false;
	static bool slider3 = false;
    static bool weighing = false;
    static bool cobotta = false;
}

std::string state::slider(std::string action)
{
	return "test";
}

std::string state::weighing(std::string action)
{
	return "test";
}

std::string state::cobotta(std::string action)
{
	return "test";
}

std::string state::PLC(std::string action)
{
	return "test";
}

state::~state()
{

}