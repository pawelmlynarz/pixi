// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

struct TimePoint {
    i64 Ticks;

    PX_ENGINE_API f64 asSeconds() const;
    PX_ENGINE_API f64 asMilliseconds() const;
    PX_ENGINE_API f64 asMicroseconds() const;
};

class GenericPlatformTime {
};

inline TimePoint operator-(TimePoint const& lhs, TimePoint const& rhs) noexcept {
    return TimePoint{lhs.Ticks - rhs.Ticks};
}

} // namespace px
