// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxcore
#include "core_globals.h"
#include "log/log.h"
#include "misc/core_delegates.h"

// pxfrontend
#include "app/pixi_application.h"
#include "rendering/renderer.h"

// pxengine
#include "pixi_engine.h"
#include "private/pixi_engine_internal.h"

// pxrhi
#include "rhi.h"

// pxeditorengine
#if WITH_EDITOR
#include "pixi_editor_engine.h"
#include "private/pixi_editor_engine_internal.h"
#endif // WITH_EDITOR

namespace px {

[[nodiscard]]
int32 EngineLoop::PreInit() {
    LogManager::Initialize();
    InitializeRHI();

    auto& Application{SimpleApplication::CreateApplication()};
    Application.InitializeRenderer(MakeShared<Renderer>());

    return 0;
}

[[nodiscard]]
int32 EngineLoop::Init() {
#if WITH_EDITOR
    int32 const Result{InitializeEditorEngine(MakeShared<ed::PixiEditorEngine>())};
#else
    int32 const Result{InitializeEngine(MakeShared<Engine>())};
#endif
    CoreDelegates::OnEngineLoopInitComplete.Broadcast();
    
    Log(Launch, Trace, "Engine loop initialized.");
    return Result;
}

void EngineLoop::Tick() {
    PixiEngine& Engine{GetEngine()};

    Engine.UpdateTimeAndHandleMaxTickRate();

    PX_TODO("StartFrame for active scenes");
    PX_TODO("Calculate FPS timings");
    PX_TODO("PollMessages");
    PX_TODO("Engine tick");
    PX_TODO("Platform and input tick");
    PX_TODO("Time and widgets(paint) tick");
    SimpleApplication::Get().Tick(Engine.GetDeltaTime());
    PX_TODO("EndFrame for active scenes");

    PX_TODO("Game & Render thread sync");

    GFrameCounter++;
}

void EngineLoop::Exit() {
    DestroyEngine();

    SimpleApplication::ShutdownApplication();
    ShutdownRHI();
}

} // namespace px
