#pragma once

#include "Crystal/Core/Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace Crystal
{

	class Log
	{
	public:
		static void Init();

		static Ref<spdlog::logger>& GetCoreLogger()   { return s_CoreLogger;   }
		static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

#define CR_CORE_CRITICAL(...) ::Crystal::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define CR_CORE_ERROR(...)    ::Crystal::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CR_CORE_WARN(...)     ::Crystal::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CR_CORE_INFO(...)     ::Crystal::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CR_CORE_TRACE(...)    ::Crystal::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define CR_CRITICAL(...)      ::Crystal::Log::GetClientLogger()->critical(__VA_ARGS__)
#define CR_ERROR(...)         ::Crystal::Log::GetClientLogger()->error(__VA_ARGS__)
#define CR_WARN(...)          ::Crystal::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CR_INFO(...)          ::Crystal::Log::GetClientLogger()->info(__VA_ARGS__)
#define CR_TRACE(...)         ::Crystal::Log::GetClientLogger()->trace(__VA_ARGS__)


