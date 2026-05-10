// © 2026 Pawel Mlynarz

#include "core.h"

#if PLATFORM_WINDOWS
#include "windows/platform_windows.h"
#else
#error Unsupported platform: no platform header available.
#endif

namespace px {

struct PXCORE_API Platform {
    static uint32 GetCurrentThreadId();
};

} // namespace px
