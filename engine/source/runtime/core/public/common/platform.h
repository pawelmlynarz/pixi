// © 2026 Pawel Mlynarz

// core
#include "core.h"

#if PLATFORM_WINDOWS
#include "windows/platform_windows.h"
#endif

namespace px{
struct PXCORE_API Platform {
    static uint32 GetCurrentThreadId();
};
}
