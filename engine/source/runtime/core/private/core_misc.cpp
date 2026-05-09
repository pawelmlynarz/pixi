// © 2026 Pawel Mlynarz

#include "core_misc.h"
#include "common/platform.h"

namespace {
int32 GGameThreadId{0};
}

void FCoreMisc::InitGameThreadId(const uint32 ThreadId) {
    GGameThreadId = ThreadId;
}

uint32 FCoreMisc::GetGameThreadId() {
    return GGameThreadId;
}

bool FCoreMisc::IsInGameThread() {
    return GetGameThreadId() == Platform::GetCurrentThreadId();
}
