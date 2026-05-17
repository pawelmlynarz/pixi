// © 2026 Pawel Mlynarz

#include "engine.h"

namespace px {

namespace {

SharedPtr<Engine> PixiEngine{nullptr};

} // namespace

void InitializeEngine(SharedPtr<Engine> const& Engine) {
    PixiEngine = Engine;
}

void DestroyEngine() {
    PixiEngine.reset();
}

SharedRef<Engine> GetEngine() {
    PX_ASSERT(PixiEngine != nullptr);
    return PixiEngine;
}

} // namespace px
