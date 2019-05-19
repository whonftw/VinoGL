#pragma once
#include "Core.h"
#include <memory>
#include "spdlog/spdlog.h"
namespace Vino
{
	class VINO_API Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger> GetClientLogger() { return s_ClientLogger; }
		inline static std::shared_ptr<spdlog::logger> GetCoreLogger() { return s_CoreLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define VN_CORE_ERROR(...) ::Vino::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define VN_CORE_INFO(...) ::Vino::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define VN_CORE_WARN(...) ::Vino::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define VN_CORE_TRACE(...) ::Vino::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define VN_CORE_FATAL(...) ::Vino::Logger::GetCoreLogger()->fatal(__VA_ARGS__);