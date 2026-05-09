// © 2026 Pawel Mlynarz

#include "core_misc.h"
#include "common/platform.h"

namespace {

int32 GameThreadId{0};
bool EngineExitRequested{false};

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
    EngineExitRequested = true;
}

bool IsEngineExitRequested() {
    return EngineExitRequested;
}

} // namespace px::core
