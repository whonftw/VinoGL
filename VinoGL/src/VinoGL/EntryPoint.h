#pragma once

#ifdef VN_PLATFORM_WINDOWS
#include "Application.h"
extern std::unique_ptr<Vino::Application> CreateApplication();
int main(int argc, char** argv)
{
	auto application = CreateApplication();
	application->Run();
}
#endif