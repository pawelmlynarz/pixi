// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "app/pixi_application.h"

// pxeditorfrontend
#include "editor_mainframe.h"

namespace px::ed {

namespace {

SharedPtr<SEditorMainFrame> EditorMainFrameWindow{nullptr};

bool CreateEditorMainFrame() {
    EditorMainFrameWindow = {MakeShared<SEditorMainFrame>()};

    EditorMainFrameWindow->Title("Pixi Editor")
        .Size({1920, 1080})
        .Decorated(true)
        .Resizable(true);

    Assert(SimpleApplication::Get().AddWindow(EditorMainFrameWindow, true));

    return true;
}

} // namespace

int32 EditorInit() {
    if (!CreateEditorMainFrame()) {
        return -1;
    }
    return 0;
}

void EditorExit() {
    EditorMainFrameWindow->DestoryNativeWindow();
    EditorMainFrameWindow.reset();
}

} // namespace px::ed
