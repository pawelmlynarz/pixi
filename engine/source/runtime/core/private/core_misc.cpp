// © 2026 Pawel Mlynarz

#include "core_misc.h"
#include "common/platform.h"

namespace {

int32 GameThreadId{0};
bool bEngineExitRequested{false};

} // namespace

namespace px::core {

void InitGameThreadId(uint32 const ThreadId) {
    GameThreadId = ThreadId;
}

uint32 GetGameThreadId() {
    return GameThreadId;
}

bool IsInGameThread() {
    return GetGameThreadId() == Platform::GetCurrentThreadId();
}

void RequestEngineExit() {
    bEngineExitRequested = true;
}

bool IsEngineExitRequested() {
    return bEngineExitRequested;
}

} // namespace px::core
