// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"

// pxEngine
#include "app/pixi_application.h"
#include "core_globals.h"
#include "log/log.h"
#include "misc/core_delegates.h"
#include "rendering/renderer.h"
#include "pixi_engine.h"
#include "private/pixi_engine_internal.h"
#include "rhi.h"

// pxEngineEditor
#if WITH_EDITOR
#include "pixi_editor_engine.h"
#include "private/pixi_editor_engine_internal.h"
#endif // WITH_EDITOR

namespace px {

[[nodiscard]]
int32 EngineLoop::preInit() {
    LogManager::initialize();
    initializeRhi();

    auto& application{SimpleApplication::createApplication()};
    application.initializeRenderer(makeShared<Renderer>());

    return 0;
}

[[nodiscard]]
int32 EngineLoop::init() {
#if WITH_EDITOR
    int32 const result{initializeEditorEngine(makeShared<ed::PixiEditorEngine>())};
#else
    int32 const result{initializeEngine(makeShared<PixiEngine>())};
#endif
    CoreDelegates::onEngineLoopInitComplete.broadcast();

    pxLog(Launch, Trace, "Engine loop initialized.");
    return result;
}

void EngineLoop::tick() {
    PixiEngine& engine{getEngine()};

    engine.updateTimeAndHandleMaxTickRate();

    pxToDo("StartFrame for active scenes");
    pxToDo("Calculate FPS timings");
    pxToDo("PollMessages");
    pxToDo("Engine tick");
    pxToDo("Platform and input tick");
    pxToDo("Time and widgets(paint) tick");
    SimpleApplication::get().tick(engine.getDeltaTime());
    pxToDo("EndFrame for active scenes");

    pxToDo("Game & Render thread sync");

    gFrameCounter++;
}

void EngineLoop::exit() {
    destroyEngine();

    SimpleApplication::shutdownApplication();
    shutdownRhi();
    
    LogManager::shutdown();
}

} // namespace px
