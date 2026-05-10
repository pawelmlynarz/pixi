// © 2026 Pawel Mlynarz

#include "launch_engine_loop.h"
#include "app/engine_application.h"

namespace px {

int32 EngineLoop::PreInit() {
    EngineApplication::Create();
    return 0;
}

int32 EngineLoop::Init() {
    GenericWindowDefinition Definition;
    EngineApplication::Get().AddWindow(Definition, true);
    return 0;
}

void EngineLoop::Tick() {
}

void EngineLoop::Exit() {
}

} // namespace px
