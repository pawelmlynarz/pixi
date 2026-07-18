// © 2026 Pawel Mlynarz

#include "tools/stack_trace.h"
#include "memory/allocator.h"
#include "memory/memory.h"

#include <stacktrace>

namespace px {

StackTrace captureStackTrace(size_t const skipFrames, size_t const captureFrames) {
    return StackTrace::current(skipFrames, captureFrames);
}

std::string printStackTraceToString(StackTrace const& stackTrace) {
    return std::to_string(stackTrace);
}

} // namespace px
