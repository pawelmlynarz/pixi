// © 2026 Pawel Mlynarz

// pxcore
#include "core_globals.h"
#include "common/platform.h"
#include "private/core_globals_internal.h"

// pxeditor
#if WITH_EDITOR
#include "private/editor_core_launch.h"
#endif // WITH_EDITOR

#include "launch_engine_loop.h"

namespace px {

namespace {

[[nodiscard]]
int32 EnginePreInit() {
    return EngineLoop::PreInit();
}

[[nodiscard]]
int32 EngineInit() {
    return EngineLoop::Init();
}

void EngineTick() {
    EngineLoop::Tick();
}

void EngineExit() {
    EngineLoop::Exit();
}

#if WITH_EDITOR
[[nodiscard]]
int32 EditorInit() {
    int32 const Result{EngineInit()};
    if (Result != 0) {
        return Result;
    }
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

// NOLINTNEXTLINE(misc-use-internal-linkage)
int32 EngineMain() {
    EngineExitGuard const ExitGuard;

    InitGameThreadId(Platform::GetCurrentThreadId());

    int32 ErrorLevel{EnginePreInit()};
    if (ErrorLevel != 0 || IsEngineExitRequested()) {
        return ErrorLevel;
    }

#if WITH_EDITOR
    ErrorLevel = EditorInit();
#else
    ErrorLevel = EngineInit();
#endif

    if (ErrorLevel != 0 || IsEngineExitRequested()) {
        return ErrorLevel;
    }

    while (!IsEngineExitRequested()) {
        EngineTick();
    }

    return ErrorLevel;
}

} // namespace px
