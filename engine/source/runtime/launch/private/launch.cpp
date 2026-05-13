// © 2026 Pawel Mlynarz

// core
#include "core_misc.h"
#include "common/platform.h"
#include "private/core_misc_internal.h"

#include "launch_engine_loop.h"

namespace px {

namespace {

EngineLoop EngineLoop;

[[nodiscard]]
int32 EnginePreInit() {
    return EngineLoop.PreInit();
}

[[nodiscard]]
int32 EngineInit() {
    return EngineLoop.Init();
}

void EngineTick() {
    EngineLoop.Tick();
}

void EngineExit() {
    EngineLoop.Exit();
}

struct EngineExitGuard {
    ~EngineExitGuard() {
        EngineExit();
    }
};

} // namespace

int32 EngineMain() {
    EngineExitGuard ExitGuard;

    InitGameThreadId(Platform::GetCurrentThreadId());

    int32 ErrorLevel{EnginePreInit()};
    if (ErrorLevel != 0 || IsEngineExitRequested())
        return ErrorLevel;

    ErrorLevel = EngineInit();
    if (ErrorLevel != 0 || IsEngineExitRequested())
        return ErrorLevel;

    while (!IsEngineExitRequested()) {
        EngineTick();
    }

    return ErrorLevel;
}

} // namespace px
