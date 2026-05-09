// © 2026 Pawel Mlynarz

#include "core_misc.h"
#include "common/platform.h"

namespace {
int32   GGameThreadId{0};
bool    GEngineExitRequested{false};
}

namespace px::core{
void InitGameThreadId(const uint32 ThreadId) {
    GGameThreadId = ThreadId;
}

uint32 GetGameThreadId() {
    return GGameThreadId;
}

bool IsInGameThread() {
    return GetGameThreadId() == Platform::GetCurrentThreadId();
}

void RequestEngineExit() {
    GEngineExitRequested = true;
}

bool IsEngineExitRequested() {
    return GEngineExitRequested;
}
}
