// © 2026 Pawel Mlynarz

#pragma once

#include "tools/delegates.h"

// spdlog
#include "spdlog/sinks/base_sink.h"

#include <mutex>

namespace px {

template <typename TMutex>
class OutputLogSink : public spdlog::sinks::base_sink<TMutex> {
  public:
    DECLARE_DELEGATE(CustomSinkCallback, std::string const&);
    
    void SetCustomCallback(CustomSinkCallback OnCustomOutputLoggerSink);

  protected:
    void sink_it_(spdlog::details::log_msg const& Msg) override;
    void flush_() override {}

  private:
    CustomSinkCallback CustomSinkCallback_;
};

template <typename TMutex>
void OutputLogSink<TMutex>::SetCustomCallback(CustomSinkCallback OnCustomOutputLoggerSink) {
    CustomSinkCallback_ = std::move(OnCustomOutputLoggerSink);
}

template <typename TMutex>
void OutputLogSink<TMutex>::sink_it_(spdlog::details::log_msg const& Msg) {
    spdlog::memory_buf_t Formatted;
    spdlog::sinks::base_sink<TMutex>::formatter_->format(Msg, Formatted);
    CustomSinkCallback_.ExecuteIfBound(fmt::to_string(Formatted));
}

#include "spdlog/details/null_mutex.h"

using OutputLogSinkMT = OutputLogSink<std::mutex>;
using OutputLogSinkST = OutputLogSink<spdlog::details::null_mutex>;

} // namespace px
