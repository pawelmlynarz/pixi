// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "platform/generic_platform/generic_platform_application_misc.h"

namespace px {

struct WindowsApplicationMisc final : GenericPlatformApplicationMisc {
    [[nodiscard]]
    static PXCORE_API UniquePtr<PlatformApplication> createApplication();
};

using PlatformApplicationMisc = WindowsApplicationMisc;

} // namespace px
