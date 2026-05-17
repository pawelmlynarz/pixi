// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxcore
#include "app/engine_application.h"

// pxengine
#include "engine.h"

// pxeditorengine
#if WITH_EDITOR
#include "editor_engine.h"
#endif // WITH_EDITOR

namespace px {

[[nodiscard]]
int32 EngineLoop::PreInit() {
    EngineRuntime::CreateApplication();
    return 0;
}

[[nodiscard]]
int32 EngineLoop::Init() {

#if WITH_EDITOR
    InitializeEditorEngine(MakeShared<ed::EditorEngine>());
#else
    InitializeEngine(MakeShared<Engine>());
#endif

    GenericWindowDefinition MainWindowDefinition;
    EngineRuntime::GetApplication().AddWindow(MainWindowDefinition, true);
    return 0;
}

void EngineLoop::Tick() {
    EngineRuntime::GetApplication().Tick();
}

void EngineLoop::Exit() {
    EngineRuntime::Shutdown();
}

} // namespace px
