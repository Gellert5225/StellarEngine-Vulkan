#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Stellar {
    class STLR_API Log {
    public:
        static void Init();
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;
    };
}

// core
#define STLR_CORE_TRACE(...) ::Stellar::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STLR_CORE_INFO(...)  ::Stellar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STLR_CORE_WARN(...)  ::Stellar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STLR_CORE_ERROR(...) ::Stellar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STLR_CORE_FATAL(...) ::Stellar::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// client
#define STLR_CLIENT_TRACE(...) ::Stellar::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define STLR_CLIENT_INFO(...)  ::Stellar::Log::GetCoreLogger()->info(__VA_ARGS__)
#define STLR_CLIENT_WARN(...)  ::Stellar::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define STLR_CLIENT_ERROR(...) ::Stellar::Log::GetCoreLogger()->error(__VA_ARGS__)
#define STLR_CLIENT_FATAL(...) ::Stellar::Log::GetCoreLogger()->fatal(__VA_ARGS__)