// © 2026 Pawel Mlynarz

#pragma once

#include "tools/delegates.h"

// spdlog
#include "spdlog/sinks/base_sink.h"
#include "spdlog/formatter.h"

#include <mutex>

namespace px {

using LogMsg = spdlog::details::log_msg;

DECLARE_DELEGATE(CustomLoggerSinkCallback, LogMsg const& /*Message*/, std::string const& /*FormattedMessage*/);

template <typename TMutex>
class OutputLogSink : public spdlog::sinks::base_sink<TMutex> {
  public:
    void SetCustomCallback(CustomLoggerSinkCallback OnCustomOutputLoggerSink);

  protected:
    void sink_it_(LogMsg const& Msg) override;
    void flush_() override {}

  private:
    CustomLoggerSinkCallback CustomSinkCallback_;
};

template <typename TMutex>
void OutputLogSink<TMutex>::SetCustomCallback(CustomLoggerSinkCallback OnCustomOutputLoggerSink) {
    CustomSinkCallback_ = std::move(OnCustomOutputLoggerSink);
}

template <typename TMutex>
void OutputLogSink<TMutex>::sink_it_(LogMsg const& Msg) {
    spdlog::memory_buf_t Formatted;
    this->formatter_->format(Msg, Formatted);

    CustomSinkCallback_.ExecuteIfBound(Msg, fmt::to_string(Formatted));
}

#include "spdlog/details/null_mutex.h"

using OutputLogSinkMT = OutputLogSink<std::mutex>;
using OutputLogSinkST = OutputLogSink<spdlog::details::null_mutex>;

} // namespace px
