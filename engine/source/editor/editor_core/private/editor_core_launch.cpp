// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "app/pixi_application.h"

// pxeditorfrontend
#include "editor_mainframe.h"

namespace px::ed {

namespace {

SharedPtr<SEditorMainFrame> editorMainFrameWindow{nullptr};

bool createEditorMainFrame() {
    editorMainFrameWindow = {makeShared<SEditorMainFrame>()};

    editorMainFrameWindow->Title("Pixi Editor")
        .Size({1920, 1080})
        .Decorated(true)
        .Resizable(true);

    pxAssert(SimpleApplication::get().addWindow(editorMainFrameWindow, true));

    return true;
}

} // namespace

int32 editorInit() {
    if (!createEditorMainFrame()) {
        return -1;
    }
    return 0;
}

void editorExit() {
    editorMainFrameWindow->destoryNativeWindow();
    editorMainFrameWindow.reset();
}

} // namespace px::ed
