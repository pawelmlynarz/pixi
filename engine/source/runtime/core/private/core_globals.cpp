// © 2026 Pawel Mlynarz

#include "core_globals.h"
#include "core_globals_internal.h"
#include "hal/platform_time.h"
#include "hal/platform_tls.h"

namespace px {

uint64 GFrameCounter{0};
uint32 GGameThreadId{0};
double GStartTime{PlatformTime::Initialize().AsSeconds()};

namespace {

bool bEngineExitRequested{false};

} // namespace

void RequestEngineExit() {
    bEngineExitRequested = true;
}

bool IsEngineExitRequested() {
    return bEngineExitRequested;
}

bool IsEditor() {
#if WITH_EDITOR
    return true;
#else
    return false;
#endif
}

void InitGameThreadId(uint32 const ThreadId) {
    GGameThreadId = ThreadId;
}

bool IsInGameThread() {
    return GGameThreadId == PlatformTLS::GetCurrentThreadId();
}

} // namespace px
