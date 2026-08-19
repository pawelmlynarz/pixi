// © 2026 Pawel Mlynarz

#include "core_globals.h"
#include "core_globals_internal.h"
#include "hal/platform_time.h"
#include "hal/platform_tls.h"

namespace px {

u64 gFrameCounter{0};
u32 gGameThreadId{0};
f64 gStartTime{PlatformTime::initialize().asSeconds()};

namespace {

bool sEngineExitRequested{false};

} // namespace

void requestEngineExit() {
    sEngineExitRequested = true;
}

bool isEngineExitRequested() {
    return sEngineExitRequested;
}

bool isEditor() {
#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}

void initGameThreadId(u32 const threadId) {
    gGameThreadId = threadId;
}

bool isInGameThread() {
    return gGameThreadId == PlatformTLS::getCurrentThreadId();
}

} // namespace px
