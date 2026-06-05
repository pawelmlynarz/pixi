// © 2026 Pawel Mlynarz

#include "pixi_editor_engine.h"
#include "pixi_editor_engine_internal.h"

// pxengine
#include "private/pixi_engine_internal.h"

namespace px::ed {

namespace {

WeakPtr<PixiEditorEngine> PixiEditorEngineInst;

} // namespace

int32 InitializeEditorEngine(SharedPtr<PixiEditorEngine> const& EditorEngine) {
    int32 const Result{InitializeEngine(EditorEngine)};
    if (Result != 0) {
        return Result;
    }
    PixiEditorEngineInst = EditorEngine;

    return 0;
}

PixiEditorEngine& GetEditorEngine() {
    auto const SharedEditorEngine{PixiEditorEngineInst.lock()};
    Assert(SharedEditorEngine != nullptr);
    return *SharedEditorEngine;
}

} // namespace px::ed
