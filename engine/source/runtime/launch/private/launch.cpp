// © 2026 Pawel Mlynarz

// core
#include "core_misc.h"
#include "common/platform.h"
#include "launch_engine_loop.h"
#include "private/core_misc_internal.h"

namespace px {
EngineLoop GEngineLoop;
}
using namespace px;

namespace {
inline int32 EnginePreInit() {
    return GEngineLoop.PreInit();
}

inline int32 EngineInit() {
    return GEngineLoop.Init();
}

inline void EngineTick() {
    GEngineLoop.Tick();
}

inline void EngineExit() {
    GEngineLoop.Exit();
}

struct EngineExitGuard {
    ~EngineExitGuard() {
        EngineExit();
    }
};
}

int32 EngineMain() {
    EngineExitGuard ExitGuard;
    
    core::InitGameThreadId(Platform::GetCurrentThreadId());

    int32 ErrorLevel{EnginePreInit()};
    if (ErrorLevel != 0 || core::IsEngineExitRequested())
        return ErrorLevel;

    ErrorLevel = EngineInit();
    if (ErrorLevel != 0 || core::IsEngineExitRequested())
        return ErrorLevel;
    
    while (!core::IsEngineExitRequested()) {
        EngineTick();
    }

    return ErrorLevel;
}
