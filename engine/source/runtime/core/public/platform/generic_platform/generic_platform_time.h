// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

struct TimePoint {
    int64 Ticks;

    PXCORE_API double asSeconds() const;
    PXCORE_API double asMilliseconds() const;
    PXCORE_API double asMicroseconds() const;
};

class GenericPlatformTime {
};

inline TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept {
    return TimePoint{lhs.Ticks - rhs.Ticks};
}

} // namespace px
