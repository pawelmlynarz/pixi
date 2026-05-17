// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxcore
#include "app/engine_application.h"
#include "private/app/engine_application_internal.h"

// pxengine
#include "engine.h"
#include "private/engine_internal.h"

// pxeditorengine
#if WITH_EDITOR
#include "editor_engine.h"
#include "private/editor_engine_internal.h"
#endif // WITH_EDITOR

namespace px {

[[nodiscard]]
int32 EngineLoop::PreInit() {
    CreateApplication();
    return 0;
}

[[nodiscard]]
int32 EngineLoop::Init() {
#if WITH_EDITOR
    int32 const Result{InitializeEditorEngine(MakeShared<ed::EditorEngine>())};
#else
    int32 const Result{InitializeEngine(MakeShared<Engine>())};
#endif
    return Result;
}

void EngineLoop::Tick() {
    GetApplication().Tick();
}

void EngineLoop::Exit() {
    DestroyEngine();
    ShutdownApplication();
}

} // namespace px
