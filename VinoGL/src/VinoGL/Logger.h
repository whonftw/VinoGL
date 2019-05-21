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
		static bool s_Initialized;
	};
}

//Core log macros
#define VN_CORE_ERROR(...) ::Vino::Logger::GetCoreLogger()->error(__VA_ARGS__);
#define VN_CORE_INFO(...) ::Vino::Logger::GetCoreLogger()->info(__VA_ARGS__);
#define VN_CORE_WARN(...) ::Vino::Logger::GetCoreLogger()->warn(__VA_ARGS__);
#define VN_CORE_TRACE(...) ::Vino::Logger::GetCoreLogger()->trace(__VA_ARGS__);
#define VN_CORE_FATAL(...) ::Vino::Logger::GetCoreLogger()->fatal(__VA_ARGS__);

//Client log macros
#define VN_CLIENT_ERROR(...) ::Vino::Logger::GetClientLogger()->error(__VA_ARGS__);
#define VN_CLIENT_INFO(...) ::Vino::Logger::GetClientLogger()->info(__VA_ARGS__);
#define VN_CLIENT_WARN(...) ::Vino::Logger::GetClientLogger()->warn(__VA_ARGS__);
#define VN_CLIENT_TRACE(...) ::Vino::Logger::GetClientLogger()->trace(__VA_ARGS__);
#define VN_CLIENT_FATAL(...) ::Vino::Logger::GetClientLogger()->fatal(__VA_ARGS__);