// © 2026 Pawel Mlynarz

#include "core_module.h"

#if PLATFORM_WINDOWS
#include "windows/platform_windows.h"
#else
#error Unsupported platform: no platform header available.
#endif

namespace px {

struct PXCORE_API Platform {
    static void Initialize();
    static void Shutdown();

    static uint32 GetCurrentThreadId();
};

} // namespace px
