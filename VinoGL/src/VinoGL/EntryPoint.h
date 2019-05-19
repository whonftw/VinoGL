#pragma once

#ifdef VN_PLATFORM_WINDOWS
#ifndef VN_OMIT_MAIN
#include "Application.h"
#include "Logger.h"
extern std::unique_ptr<Vino::Application> CreateApplication();
int main(int argc, char** argv)
{
	Vino::Logger::Init();
	VN_CORE_INFO("Logger Initialized");
	auto application = CreateApplication();
	application->Run();
}
#endif
#endif