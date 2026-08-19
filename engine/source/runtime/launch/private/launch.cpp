// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxEngine
#include "core_globals.h"
#include "hal/platform_tls.h"
#include "private/core_globals_internal.h"
#include "misc/core_delegates.h"

// pxEngineEditor
#if WITH_EDITOR
#include "private/editor_core_launch.h"
#endif // WITH_EDITOR

namespace px {

namespace {

[[nodiscard]]
i32 enginePreInit() {
    return EngineLoop::preInit();
}

[[nodiscard]]
i32 engineInit() {
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
i32 editorInit() {
    i32 result{engineInit()};
    if (result != 0) {
        return result;
    }
    result = ed::editorInit();
    if (result == 0) {
        CoreDelegates::onEditorInitComplete.broadcast();
    }
    return result;
}

void editorExit() {
    ed::editorExit();
    engineExit();
}
#endif // WITH_EDITOR

struct EngineExitGuard {
    ~EngineExitGuard() {
#if WITH_EDITOR
        editorExit();
#else
        engineExit();
#endif
    }
};

} // namespace

// NOLINTNEXTLINE(misc-use-internal-linkage)
i32 engineMain() {
    EngineExitGuard const exitGuard;

    initGameThreadId(PlatformTLS::getCurrentThreadId());

    i32 errorLevel{enginePreInit()};
    if (errorLevel != 0 || isEngineExitRequested()) {
        return errorLevel;
    }

#if WITH_EDITOR
    errorLevel = editorInit();
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
