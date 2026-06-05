// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "../../editor_engine/public/pixi_editor_engine.h"
#include "app/pixi_application.h"
#include "widgets/swindow.h"

// imgui
#if WITH_IMGUI
#include "imgui.h"
#endif

namespace px::ed {

namespace {

class SEditorMainFrame final : public SWindow {
  public:
    SEditorMainFrame() = default;

  protected:
    void DrawImGui() override {
        auto& EdEngine{GetEditorEngine()};

        ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoResize);
        {
            ImGui::Text("FPS: %.2f", EdEngine.GetFPS());
        }
        ImGui::End();
    }
};
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
