// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxcore
#include "app/simple_application.h"
#include "widgets/swindow.h"

namespace px::ed {

namespace {

class SEditorWindow final : public SWindow {
  public:
    virtual void Draw() override {
    }
};
SharedPtr<SEditorWindow> MainEditorWindow{nullptr};

bool CreateMainEditorWindow() {
    MainEditorWindow = {MakeShared<SEditorWindow>()};

    MainEditorWindow->Title("Pixi Editor")
        .Size({1920, 1080})
        .Decorated(true)
        .Resizable(true);

    Assert(SimpleApplication::Get().AddWindow(MainEditorWindow, true));

    return true;
}

} // namespace

int32 EditorInit() {
    if (!CreateMainEditorWindow())
        return -1;
    return 0;
}

void EditorExit() {
    MainEditorWindow->DestoryNativeWindow();
    MainEditorWindow.reset();
}

} // namespace px::ed
