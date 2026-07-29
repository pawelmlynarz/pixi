// © 2026 Pawel Mlynarz

#include "log/log.h"

// spdlog
#include "spdlog/pattern_formatter.h"

namespace px {

namespace {

constexpr std::string_view defaultPattern{"%^[%T][%n][%L]: %v%$"};

using LoggersMap = std::unordered_map<std::string_view, SharedPtr<Logger>>;
std::optional<LoggersMap> sRegisteredLoggers;

struct LevelFormatter : spdlog::custom_flag_formatter {
    void format(spdlog::details::log_msg const& msg, std::tm const&, spdlog::memory_buf_t& dest) override {

        std::string_view level{"Unknown"};

        switch (msg.level) {
        case spdlog::level::trace: level = "Trace"; break;
        case spdlog::level::debug: level = "Debug"; break;
        case spdlog::level::info: level = "Info"; break;
        case spdlog::level::warn: level = "Warn"; break;
        case spdlog::level::err: level = "Error"; break;
        case spdlog::level::critical: level = "Critical"; break;
        default: break;
        }

        dest.append(level.data(), level.data() + level.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override {
        return spdlog::details::make_unique<LevelFormatter>();
    }

    static UniquePtr<spdlog::pattern_formatter> createFormatter() {
        auto formatter{makeUnique<spdlog::pattern_formatter>()};
        formatter->add_flag<LevelFormatter>('L').set_pattern(defaultPattern.data());
        return formatter;
    }
};

void registerEngineLoggers() {
    DEFINE_LOG_CATEGORY(Launch);
    DEFINE_LOG_CATEGORY(Core);
    DEFINE_LOG_CATEGORY(RHI);
}

} // namespace

void LogManager::initialize() {
    sRegisteredLoggers = LoggersMap();
    registerEngineLoggers();
}

void LogManager::shutdown() {
    sRegisteredLoggers.reset();
}

void LogManager::registerLogger(std::string_view const& categoryName, std::shared_ptr<Logger> logger) {
    pxAssert(sRegisteredLoggers.has_value());

    auto const foundLogger{sRegisteredLoggers->find(categoryName)};
    pxAssertMsgf(foundLogger == sRegisteredLoggers->end(), "Logger with name provided is already registered.");

    (*sRegisteredLoggers)[categoryName] = std::move(logger);
    (*sRegisteredLoggers)[categoryName]->set_pattern(defaultPattern.data());
    (*sRegisteredLoggers)[categoryName]->set_formatter(LevelFormatter::createFormatter());
    (*sRegisteredLoggers)[categoryName]->set_level(spdlog::level::trace);
}

void LogManager::registerOutputLogSinkMt(SharedPtr<OutputLogSinkMT> const& outputLogSinkMt) {
    pxAssert(sRegisteredLoggers.has_value());

    for (auto& logger : std::views::values(*sRegisteredLoggers)) {
        logger->sinks().emplace_back(outputLogSinkMt);
        outputLogSinkMt->set_pattern(defaultPattern.data());
        outputLogSinkMt->set_formatter(LevelFormatter::createFormatter());
        outputLogSinkMt->set_level(toNative(sGlobalLogLevel));
    }
}

bool LogManager::isReady() {
    return sRegisteredLoggers.has_value();
}

Logger& LogManager::getLogger(std::string_view const& categoryName) {
    pxAssert(sRegisteredLoggers.has_value());

    auto const foundLogger{sRegisteredLoggers->find(categoryName)};
    pxAssertMsgf(foundLogger != sRegisteredLoggers->end(), "Logger with provided name was not registered.");

    return *foundLogger->second;
}

} // namespace px
