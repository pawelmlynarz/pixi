// © 2026 Pawel Mlynarz

#pragma once

#include "app/platform_application_misc.h"

namespace px {

struct WindowsApplicationMisc final : GenericPlatformApplicationMisc {
    [[nodiscard]]
    static PXCORE_API UniquePtr<PlatformApplication> CreateApplication();
};

using PlatformApplicationMisc = WindowsApplicationMisc;

} // namespace px
