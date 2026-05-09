// © 2026 Pawel Mlynarz

// core
#include "core_misc.h"
#include "common/platform.h"

int32 EngineMain() {
    FCoreMisc::InitGameThreadId(Platform::GetCurrentThreadId());
    return 0;
}
