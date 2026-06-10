// © 2026 Pawel Mlynarz

#pragma once

#include "log_sink.h"

// spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <string_view>
#include <unordered_map>

namespace px {

enum class ELogVerbosity : uint8_t {
    Trace,
    Info,
    Warning,
    Error,
    MAX
};

using Logger = spdlog::logger;

struct LogManager {
    static constexpr ELogVerbosity sGlobalLogLevel{ELogVerbosity::MAX};

    static PXCORE_API void Initialize();

    static PXCORE_API void RegisterLogger(std::string_view const& CategoryName, SharedPtr<Logger> Logger);

    static PXCORE_API Logger& GetLogger(std::string_view const& CategoryName);

    static PXCORE_API void RegisterOutputLogSinkMT(SharedPtr<OutputLogSinkMT> OutputLogSinkMT);
};

template <ELogVerbosity Verbosity, typename... TArgs>
void LogImpl(std::string_view const Category, TArgs&&... Args) {
    if constexpr (Verbosity < LogManager::sGlobalLogLevel) {
        auto& Logger{LogManager::GetLogger(Category)};

        if constexpr (Verbosity == ELogVerbosity::Trace) {
            Logger.trace(std::forward<TArgs>(Args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Info) {
            Logger.info(std::forward<TArgs>(Args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Warning) {
            Logger.warn(std::forward<TArgs>(Args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Error) {
            Logger.error(std::forward<TArgs>(Args)...);
        }
    }
}

} // namespace px

#define DEFINE_LOG_CATEGORY(Category) \
    px::LogManager::RegisterLogger(#Category, spdlog::stdout_color_mt(#Category))

#define DEFINE_OUTPUT_LOG_SINK(OutputLogSink) \
    px::LogManager::RegisterOutputLogSinkMT(OutputLogSink)

#define Log(Category, Verbosity, ...) \
    LogImpl<px::ELogVerbosity::Verbosity>(#Category, __VA_ARGS__)
