// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_platform_time.h"

namespace px {

double TimePoint::AsSeconds() const {
    return static_cast<double>(Ticks) / 1000000.0;
}

double TimePoint::AsMilliseconds() const {
    return static_cast<double>(Ticks) / 1000.0;
}

double TimePoint::AsMicroseconds() const {
    return static_cast<double>(Ticks);
}

} // namespace px
