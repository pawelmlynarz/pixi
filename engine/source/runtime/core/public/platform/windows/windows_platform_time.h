// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "platform/generic_platform/generic_platform_time.h"

namespace px {

class PXCORE_API WindowsPlatformTime final : public GenericPlatformTime {
  public:
    static TimePoint initialize() noexcept;

    static TimePoint now();
    static TimePoint from(TimePoint startingTime);
    static TimePoint delta(TimePoint startingTime, TimePoint endingTime);
};

using PlatformTime = WindowsPlatformTime;

} // namespace px
