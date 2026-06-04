// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

namespace px {

struct TimePoint {
    int64 Ticks;

    PXCORE_API double AsSeconds() const;
    PXCORE_API double AsMilliseconds() const;
    PXCORE_API double AsMicroseconds() const;
};

class GenericPlatformTime {
};

inline TimePoint operator-(TimePoint const& Lhs, TimePoint const& Rhs) noexcept {
    return TimePoint{Lhs.Ticks - Rhs.Ticks};
}

} // namespace px

#include COMPILED_PLATFORM_HEADER(platform_time.h)
