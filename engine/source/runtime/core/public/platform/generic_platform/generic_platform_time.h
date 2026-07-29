// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

struct TimePoint {
    int64 Ticks;

    PX_ENGINE_API double asSeconds() const;
    PX_ENGINE_API double asMilliseconds() const;
    PX_ENGINE_API double asMicroseconds() const;
};

class GenericPlatformTime {
};

inline TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept {
    return TimePoint{lhs.Ticks - rhs.Ticks};
}

} // namespace px
