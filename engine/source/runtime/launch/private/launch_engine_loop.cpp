// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxui
#include "app/simple_application.h"

// pxengine
#include "engine.h"
#include "private/engine_internal.h"

// pxrhi
#include "rhi.h"

// pxrenderer
#include "renderer.h"

// pxeditorengine
#if WITH_EDITOR
#include "editor_engine.h"
#include "private/editor_engine_internal.h"
#endif // WITH_EDITOR

namespace px {

[[nodiscard]]
int32 EngineLoop::PreInit() {
    auto& Application{SimpleApplication::CreateApplication()};
    InitializeRHI();
    Application.InitializeRenderer(MakeShared<Renderer>());
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
    SimpleApplication::Get().Tick();
}

void EngineLoop::Exit() {
    DestroyEngine();
    SimpleApplication::ShutdownApplication();
    ShutdownRHI();
}

} // namespace px
