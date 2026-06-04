// © 2026 Pawel Mlynarz

#include "editor_core_launch.h"

// pxfrontend
#include "../../editor_engine/public/pixi_editor_engine.h"
#include "app/pixi_application.h"
#include "widgets/swindow.h"
#include "rendering/renderer.h"
#if WITH_IMGUI
#include "rendering/imgui_renderer.h"

// imgui
#include "imgui.h"
#endif

namespace px::ed {

namespace {

class SEditorWindow final : public SWindow {
  public:
    SEditorWindow() {
        auto& R = dynamic_cast<Renderer&>(SimpleApplication::Get().GetRenderer());
        ImGui::SetCurrentContext(static_cast<ImGuiContext*>(R.GetImGuiRenderer().GetImguiContext()));
    }

  protected:
    virtual void DrawImGui() override {
        auto& EdEngine{GetEditorEngine()};

        ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoResize);
        {
            ImGui::Text("FPS: %.2f", EdEngine.GetFPS());
        }
        ImGui::End();
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
