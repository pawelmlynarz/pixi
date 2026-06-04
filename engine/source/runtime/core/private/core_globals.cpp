// © 2026 Pawel Mlynarz

#include "core_globals.h"
#include "core_globals_internal.h"
#include "common/platform.h"

namespace px {

uint64 GFrameCounter{0};
uint32 GGameThreadId{0};
double GStartTime{0.0};

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
    return GGameThreadId == Platform::GetCurrentThreadId();
}

} // namespace px
