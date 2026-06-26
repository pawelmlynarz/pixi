// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_platform_time.h"

namespace px {

double TimePoint::asSeconds() const {
    return static_cast<double>(Ticks) / 1000000.0;
}

double TimePoint::asMilliseconds() const {
    return static_cast<double>(Ticks) / 1000.0;
}

double TimePoint::asMicroseconds() const {
    return static_cast<double>(Ticks);
}

} // namespace px
