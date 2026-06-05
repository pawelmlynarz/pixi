// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "platform/generic_platform/generic_platform_time.h"

namespace px {

class PXCORE_API WindowsPlatformTime final : public GenericPlatformTime {
  public:
    static TimePoint Initialize() noexcept;

    static TimePoint Now();
    static TimePoint From(TimePoint StartingTime);
    static TimePoint Delta(TimePoint StartingTime, TimePoint EndingTime);
};

using PlatformTime = WindowsPlatformTime;

} // namespace px
