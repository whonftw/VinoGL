#include "Logger.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Vino
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::s_ClientLogger;
	bool Logger::s_Initialized;

	void Logger::Init()
	{
		if (!s_Initialized)
		{
			//TODO: Get rid of magic string
			spdlog::set_pattern("%^[%T] %n: %v%$");
			s_CoreLogger = spdlog::stdout_color_mt("VinoGL");
			s_CoreLogger->set_level(spdlog::level::trace);
			s_ClientLogger = spdlog::stdout_color_mt("Application");
			s_ClientLogger->set_level(spdlog::level::trace);
			s_Initialized = true;
		}
	}
}
