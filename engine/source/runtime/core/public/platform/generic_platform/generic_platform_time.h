// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

struct TimePoint {
    int64 Ticks;

    PXENGINE_API double asSeconds() const;
    PXENGINE_API double asMilliseconds() const;
    PXENGINE_API double asMicroseconds() const;
};

class GenericPlatformTime {
};

inline TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept {
    return TimePoint{lhs.Ticks - rhs.Ticks};
}

} // namespace px
