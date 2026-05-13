// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"
#include "app/engine_application.h"

namespace px {

[[nodiscard]]
int32 EngineLoop::PreInit() {
    EngineRuntime::CreateApplication();
    return 0;
}

[[nodiscard]]
int32 EngineLoop::Init() {
    GenericWindowDefinition MainWindowDefinition;
    EngineRuntime::GetApplication().AddWindow(MainWindowDefinition, true);
    return 0;
}

void EngineLoop::Tick() {
    EngineRuntime::GetApplication().PollMessages();
}

void EngineLoop::Exit() {
    EngineRuntime::Shutdown();
}

} // namespace px
