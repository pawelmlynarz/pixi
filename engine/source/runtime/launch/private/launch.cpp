// © 2026 Pawel Mlynarz

// pxcore
#include "core_misc.h"
#include "common/platform.h"
#include "private/core_misc_internal.h"

// pxeditor
#if WITH_EDITOR
#include "editor_core_launch.h"
#endif // WITH_EDITOR

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

#if WITH_EDITOR
[[nodiscard]]
int32 EditorInit() {
    int32 const Result{EngineInit()};
    if (!Result)
        return Result;
    return ed::EditorInit();
}

void EditorExit() {
    ed::EditorExit();
    EngineExit();
}
#endif // WITH_EDITOR

struct EngineExitGuard {
    ~EngineExitGuard() {
#if WITH_EDITOR
        EditorExit();
#else
        EngineExit();
#endif
    }
};

} // namespace

int32 EngineMain() {
    EngineExitGuard ExitGuard;

    InitGameThreadId(Platform::GetCurrentThreadId());

    int32 ErrorLevel{EnginePreInit()};
    if (ErrorLevel != 0 || IsEngineExitRequested())
        return ErrorLevel;

#if WITH_EDITOR
    ErrorLevel = EditorInit();
#else
    ErrorLevel = EngineInit();
#endif

    if (ErrorLevel != 0 || IsEngineExitRequested())
        return ErrorLevel;

    while (!IsEngineExitRequested()) {
        EngineTick();
    }

    return ErrorLevel;
}

} // namespace px
