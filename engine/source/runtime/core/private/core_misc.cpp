// © 2026 Pawel Mlynarz

#include "core_misc.h"
#include "core_misc_internal.h"
#include "common/platform.h"

namespace px {

namespace {

uint32 GameThreadId{0};
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
    GameThreadId = ThreadId;
}

uint32 GetGameThreadId() {
    return GameThreadId;
}

bool IsInGameThread() {
    return GetGameThreadId() == Platform::GetCurrentThreadId();
}

} // namespace px
