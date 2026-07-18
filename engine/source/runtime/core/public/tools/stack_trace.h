// © 2026 Pawel Mlynarz

#pragma once

#include "memory/stl_allocator.h"
#include "tools/compiler.h"

#include <stacktrace>
#include <string>

namespace px {

using StackTrace = std::basic_stacktrace<
    StlAllocator<std::stacktrace_entry, Mallocator>>;

PXENGINE_API StackTrace captureStackTrace(size_t skipFrames = 1, size_t captureFrames = 6);

PXENGINE_API std::string printStackTraceToString(StackTrace const& stackTrace);

} // namespace px
