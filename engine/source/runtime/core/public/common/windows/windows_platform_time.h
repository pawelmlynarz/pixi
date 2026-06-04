// © 2026 Pawel Mlynarz

#pragma once

#include "common/platform_time.h"

namespace px {

class PXCORE_API WindowsPlatformTime final : public GenericPlatformTime {
  public:
    static void Initialize();
    static void Shutdown();

    static TimePoint Now();
    static TimePoint From(TimePoint StartingTime);
    static TimePoint Delta(TimePoint StartingTime, TimePoint EndingTime);
};

using PlatformTime = WindowsPlatformTime;

} // namespace px
