// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "app/pixi_application.h"

// pxeditorfrontend
#include "editor_mainframe.h"

namespace px::ed {

namespace {

SharedPtr<EditorMainFrameWindow> editorMainFrameWindow{nullptr};

bool createEditorMainFrame() {
    editorMainFrameWindow = {makeShared<EditorMainFrameWindow>()};

    editorMainFrameWindow->title("Pixi Editor")
        .size({1920, 1080})
        .decorated(true)
        .resizable(true);

    return SimpleApplication::get().addWindow(editorMainFrameWindow, true);
}

} // namespace

int32 editorInit() {
    pxAssert(!editorMainFrameWindow);

    if (!createEditorMainFrame()) {
        return -1;
    }
    return 0;
}

void editorExit() {
    if (editorMainFrameWindow) {
        editorMainFrameWindow->destoryNativeWindow();
        editorMainFrameWindow.reset();
    }
}

} // namespace px::ed
