// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"
#include "log_sink.h"

// spdlog
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#include <string_view>

namespace px {

enum class ELogVerbosity : uint8_t {
    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Critical,
    Off
};

constexpr spdlog::level::level_enum toNative(ELogVerbosity const verbosity) {
    return static_cast<spdlog::level::level_enum>(verbosity);
}

constexpr ELogVerbosity fromNative(spdlog::level::level_enum const level) {
    return static_cast<ELogVerbosity>(level);
}

using Logger = spdlog::logger;

struct LogManager {
    static constexpr ELogVerbosity sGlobalLogLevel{ELogVerbosity::Trace};

    static PXENGINE_API void initialize();
    
    static PXENGINE_API void shutdown();

    static PXENGINE_API void registerLogger(std::string_view const& categoryName, SharedPtr<Logger> logger);

    static PXENGINE_API Logger& getLogger(std::string_view const& categoryName);

    static PXENGINE_API void registerOutputLogSinkMt(SharedPtr<OutputLogSinkMT> const& outputLogSinkMt);
    
    static PXENGINE_API bool isReady();
};

template <ELogVerbosity Verbosity, typename... TArgs>
void logImpl(std::string_view const category, TArgs&&... args) {
    if constexpr (Verbosity >= LogManager::sGlobalLogLevel) {
        if (!LogManager::isReady()) {
            return;
        }
        auto& logger{LogManager::getLogger(category)};

        if constexpr (Verbosity == ELogVerbosity::Trace) {
            logger.trace(std::forward<TArgs>(args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Info) {
            logger.info(std::forward<TArgs>(args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Warning) {
            logger.warn(std::forward<TArgs>(args)...);
        } else if constexpr (Verbosity == ELogVerbosity::Error) {
            logger.error(std::forward<TArgs>(args)...);
        } else {
            static_assert(false, "Requested verbosity currently disabled.");
        }
    }
}

} // namespace px

#define DEFINE_LOG_CATEGORY(category) \
    px::LogManager::registerLogger(#category, spdlog::stdout_color_mt(#category))

#define DEFINE_OUTPUT_LOG_SINK(outputLogSink) \
    px::LogManager::registerOutputLogSinkMt(outputLogSink)

#define pxLog(category, verbosity, ...) \
    logImpl<px::ELogVerbosity::verbosity>(#category, __VA_ARGS__)
