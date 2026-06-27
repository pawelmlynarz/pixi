// © 2026 Pawel Mlynarz

#include "core_globals.h"
#include "core_globals_internal.h"
#include "hal/platform_time.h"
#include "hal/platform_tls.h"

namespace px {

uint64 gFrameCounter{0};
uint32 gGameThreadId{0};
double gStartTime{PlatformTime::initialize().asSeconds()};

namespace {

bool bEngineExitRequested{false};

} // namespace

void requestEngineExit() {
    bEngineExitRequested = true;
}

bool isEngineExitRequested() {
    return bEngineExitRequested;
}

bool isEditor() {
#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}

void initGameThreadId(uint32 const threadId) {
    gGameThreadId = threadId;
}

bool isInGameThread() {
    return gGameThreadId == PlatformTLS::getCurrentThreadId();
}

} // namespace px
