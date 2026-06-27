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
    void setCustomCallback(CustomLoggerSinkCallback onCustomOutputLoggerSink);

  protected:
    void sink_it_(LogMsg const& msg) override;
    void flush_() override {}

  private:
    CustomLoggerSinkCallback customSinkCallback_;
};

template <typename TMutex>
void OutputLogSink<TMutex>::setCustomCallback(CustomLoggerSinkCallback onCustomOutputLoggerSink) {
    customSinkCallback_ = std::move(onCustomOutputLoggerSink);
}

template <typename TMutex>
void OutputLogSink<TMutex>::sink_it_(LogMsg const& msg) {
    spdlog::memory_buf_t formatted;
    this->formatter_->format(msg, formatted);

    customSinkCallback_.executeIfBound(msg, fmt::to_string(formatted));
}

#include "spdlog/details/null_mutex.h"

using OutputLogSinkMT = OutputLogSink<std::mutex>;
using OutputLogSinkST = OutputLogSink<spdlog::details::null_mutex>;

} // namespace px
