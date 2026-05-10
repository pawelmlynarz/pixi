// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/utility.h"

namespace px {

struct GenericPlatformApplicationMisc {
    static PXCORE_API UniquePtr<class PlatformApplication> CreateApplication();
};

} // namespace px

#if PLATFORM_WINDOWS
#include "windows/windows_application_misc.h"
#else
#error Unsupported platform: no application misc implementation available.
#endif // PLATFORM_WINDOWS
