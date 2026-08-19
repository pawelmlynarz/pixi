// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_platform_time.h"

namespace px {

f64 TimePoint::asSeconds() const {
    return static_cast<f64>(Ticks) / 1000000.0;
}

f64 TimePoint::asMilliseconds() const {
    return static_cast<f64>(Ticks) / 1000.0;
}

f64 TimePoint::asMicroseconds() const {
    return static_cast<f64>(Ticks);
}

} // namespace px
