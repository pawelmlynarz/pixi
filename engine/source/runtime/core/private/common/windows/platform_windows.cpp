// � 2026 Pawel Mlynarz

#include "common/platform.h"
#include "common/platform_time.h"
#include "core_globals.h"

namespace px {

void Platform::Initialize() {
    PlatformTime::Initialize();
    GStartTime = PlatformTime::Now().AsSeconds();
}

void Platform::Shutdown() {
    PlatformTime::Shutdown();
}

uint32 Platform::GetCurrentThreadId() {
    return ::GetCurrentThreadId();
};

} // namespace px
