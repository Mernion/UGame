#pragma once
#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace UGame
{
	class UGAME_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return coreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return clientLogger; }

	private:

		static std::shared_ptr<spdlog::logger> coreLogger;
		static std::shared_ptr<spdlog::logger> clientLogger;
	};

}

// engine level logs
#define UG_CORE_TRACE(...) ::UGame::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define UG_CORE_INFO(...)  ::UGame::Log::GetCoreLogger()->info(__VA_ARGS__);
#define UG_CORE_WARN(...)  ::UGame::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define UG_CORE_ERROR(...) ::UGame::Log::GetCoreLogger()->error(__VA_ARGS__);
#define UG_CORE_FATAL(...) ::UGame::Log::GetCoreLogger()->fatal(__VA_ARGS__);

// sandbox app logs
#define UG_TRACE(...) ::UGame::Log::GetClientLogger()->trace(__VA_ARGS__);
#define UG_INFO(...)  ::UGame::Log::GetClientLogger()->info(__VA_ARGS__);
#define UG_WARN(...)  ::UGame::Log::GetClientLogger()->warn(__VA_ARGS__);
#define UG_ERROR(...) ::UGame::Log::GetClientLogger()->error(__VA_ARGS__);
#define UG_FATAL(...) ::UGame::Log::GetClientLogger()->fatal(__VA_ARGS__);