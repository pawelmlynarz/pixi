// © 2026 Pawel Mlynarz

#include "log/log.h"

// spdlog
#include "spdlog/pattern_formatter.h"

namespace px {

namespace {

constexpr std::string_view DefaultPattern{"%^[%T][%n][%L]: %v%$"};

using LoggersMap = std::unordered_map<std::string_view, SharedPtr<Logger>>;
LoggersMap RegisteredLoggers;

struct LevelFormatter : spdlog::custom_flag_formatter {
    void format(spdlog::details::log_msg const& Msg, std::tm const&, spdlog::memory_buf_t& Dest) override {

        std::string_view Level{"Unknown"};

        switch (Msg.level) {
        case spdlog::level::trace: Level = "Trace"; break;
        case spdlog::level::debug: Level = "Debug"; break;
        case spdlog::level::info: Level = "Info"; break;
        case spdlog::level::warn: Level = "Warn"; break;
        case spdlog::level::err: Level = "Error"; break;
        case spdlog::level::critical: Level = "Critical"; break;
        default: break;
        }

        Dest.append(Level.data(), Level.data() + Level.size());
    }

    std::unique_ptr<custom_flag_formatter> clone() const override {
        return spdlog::details::make_unique<LevelFormatter>();
    }

    static UniquePtr<spdlog::pattern_formatter> CreateFormatter() {
        auto Formatter{MakeUnique<spdlog::pattern_formatter>()};
        Formatter->add_flag<LevelFormatter>('L').set_pattern(DefaultPattern.data());
        return Formatter;
    }
};

void RegisterEngineLoggers() {
    DEFINE_LOG_CATEGORY(Launch);
    DEFINE_LOG_CATEGORY(Core);
    DEFINE_LOG_CATEGORY(RHI);
}

} // namespace

void LogManager::Initialize() {
    RegisterEngineLoggers();
}

void LogManager::RegisterLogger(std::string_view const& CategoryName, std::shared_ptr<Logger> Logger) {
    auto const FoundLogger{RegisteredLoggers.find(CategoryName)};
    AssertMsgf(FoundLogger == RegisteredLoggers.end(), "Logger with name provided is already registered.");

    RegisteredLoggers[CategoryName] = std::move(Logger);
    RegisteredLoggers[CategoryName]->set_pattern(DefaultPattern.data());
    RegisteredLoggers[CategoryName]->set_formatter(LevelFormatter::CreateFormatter());
    RegisteredLoggers[CategoryName]->set_level(spdlog::level::trace);
}

void LogManager::RegisterOutputLogSinkMT(SharedPtr<OutputLogSinkMT> OutputLogSinkMT) {
    for (auto& Logger : std::views::values(RegisteredLoggers)) {
        Logger->sinks().emplace_back(OutputLogSinkMT);
        OutputLogSinkMT->set_pattern(DefaultPattern.data());
        OutputLogSinkMT->set_formatter(LevelFormatter::CreateFormatter());
        OutputLogSinkMT->set_level(ToNative(sGlobalLogLevel));
    }
}

Logger& LogManager::GetLogger(std::string_view const& CategoryName) {
    auto const FoundLogger{RegisteredLoggers.find(CategoryName)};
    AssertMsgf(FoundLogger != RegisteredLoggers.end(), "Logger with provided name was not registered.");

    return *FoundLogger->second;
}

} // namespace px
