// © 2026 Pawel Mlynarz

#include "editor_engine.h"

namespace px::ed {

namespace {

SharedPtr<EditorEngine> PixiEditorEngine{nullptr};

} // namespace

void InitializeEditorEngine(SharedPtr<EditorEngine> const& EditorEngine) {
    PixiEditorEngine = EditorEngine;
    InitializeEngine(PixiEditorEngine);
}

SharedRef<EditorEngine> GetEditorEngine() {
    PX_ASSERT(PixiEditorEngine != nullptr);
    return PixiEditorEngine;
}

} // namespace px::ed
