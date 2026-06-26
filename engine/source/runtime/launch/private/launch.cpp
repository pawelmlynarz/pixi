// © 2026 Pawel Mlynarz

// pxcore
#include "core_globals.h"
#include "hal/platform_tls.h"
#include "private/core_globals_internal.h"

// pxeditor
#if WITH_EDITOR
#include "private/editor_core_launch.h"
#endif // WITH_EDITOR

#include "launch_engine_loop.h"

namespace px {

namespace {

[[nodiscard]]
int32 enginePreInit() {
    return EngineLoop::preInit();
}

[[nodiscard]]
int32 engineInit() {
    return EngineLoop::init();
}

void engineTick() {
    EngineLoop::tick();
}

void engineExit() {
    EngineLoop::exit();
}

#if WITH_EDITOR
[[nodiscard]]
int32 EditorInit() {
    int32 const Result{engineInit()};
    if (Result != 0) {
        return Result;
    }
    return ed::editorInit();
}

void EditorExit() {
    ed::editorExit();
    engineExit();
}
#endif // WITH_EDITOR

struct EngineExitGuard {
    ~EngineExitGuard() {
#if WITH_EDITOR
        EditorExit();
#else
        engineExit();
#endif
    }
};

} // namespace

// NOLINTNEXTLINE(misc-use-internal-linkage)
int32 engineMain() {
    EngineExitGuard const exitGuard;

    initGameThreadId(PlatformTLS::getCurrentThreadId());

    int32 errorLevel{enginePreInit()};
    if (errorLevel != 0 || isEngineExitRequested()) {
        return errorLevel;
    }

#if WITH_EDITOR
    errorLevel = EditorInit();
#else
    errorLevel = engineInit();
#endif

    if (errorLevel != 0 || isEngineExitRequested()) {
        return errorLevel;
    }

    while (!isEngineExitRequested()) {
        engineTick();
    }

    return errorLevel;
}

} // namespace px
