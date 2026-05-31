// © 2026 Pawel Mlynarz

#include "editor_engine.h"
#include "editor_engine_internal.h"

// pxengine
#include "private/engine_internal.h"

namespace px::ed {

namespace {

WeakPtr<EditorEngine> PixiEditorEngine;

} // namespace

int32 InitializeEditorEngine(SharedPtr<EditorEngine> const& EditorEngine) {
    int32 const Result{InitializeEngine(EditorEngine)};
    if (!Result)
        return Result;
    PixiEditorEngine = EditorEngine;

    return 0;
}

EditorEngine& GetEditorEngine() {
    auto const SharedEditorEngine{PixiEditorEngine.lock()};
    Assert(SharedEditorEngine != nullptr);
    return *SharedEditorEngine;
}

} // namespace px::ed
