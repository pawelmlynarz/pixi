// © 2026 Pawel Mlynarz

#include "engine.h"
#include "engine_internal.h"

namespace px {

namespace {

SharedPtr<Engine> PixiEngine{nullptr};

} // namespace

int32 InitializeEngine(SharedPtr<Engine> const& Engine) {
    PixiEngine = Engine;
    return 0;
}

void DestroyEngine() {
    PixiEngine.reset();
}

Engine& GetEngine() {
    Assert(PixiEngine != nullptr);
    return *PixiEngine;
}

} // namespace px
