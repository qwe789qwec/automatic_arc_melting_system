#include <chrono>
#include <thread>

#include <stdio.h>
#include <unistd.h>

#include "main_process/process_state.hpp"

state::state()
{
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