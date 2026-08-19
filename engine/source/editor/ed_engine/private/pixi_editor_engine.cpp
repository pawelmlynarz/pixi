// © 2026 Pawel Mlynarz

#include "pixi_editor_engine.h"
#include "pixi_editor_engine_internal.h"
#include "private/pixi_engine_internal.h"

namespace px::ed {

namespace {

WeakPtr<PixiEditorEngine> sPixiEditorEngine;

} // namespace

i32 initializeEditorEngine(SharedPtr<PixiEditorEngine> const& editorEngine) {
    i32 const result{initializeEngine(editorEngine)};
    if (result != 0) {
        return result;
    }
    sPixiEditorEngine = editorEngine;

    return 0;
}

PixiEditorEngine& getEditorEngine() {
    auto const sharedEditorEngine{sPixiEditorEngine.lock()};
    pxAssert(sharedEditorEngine != nullptr);
    return *sharedEditorEngine;
}

} // namespace px::ed
