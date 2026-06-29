// © 2026 Pawel Mlynarz

#include "pixi_editor_engine.h"
#include "pixi_editor_engine_internal.h"
#include "private/pixi_engine_internal.h"

namespace px::ed {

namespace {

WeakPtr<PixiEditorEngine> pixiEditorEngineInst;

} // namespace

int32 initializeEditorEngine(SharedPtr<PixiEditorEngine> const& editorEngine) {
    int32 const result{initializeEngine(editorEngine)};
    if (result != 0) {
        return result;
    }
    pixiEditorEngineInst = editorEngine;

    return 0;
}

PixiEditorEngine& getEditorEngine() {
    auto const sharedEditorEngine{pixiEditorEngineInst.lock()};
    pxAssert(sharedEditorEngine != nullptr);
    return *sharedEditorEngine;
}

} // namespace px::ed
