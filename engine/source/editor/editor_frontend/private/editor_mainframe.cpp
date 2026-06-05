// © 2026 Pawel Mlynarz

#include "editor_mainframe.h"

// pxfrontend
#include "pixi_editor_engine.h"

namespace px::ed {

void SEditorMainFrame::DrawImGui() {
    auto& EdEngine{GetEditorEngine()};

    ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoResize);
    {
        ImGui::Text("FPS: %.2f", EdEngine.GetFPS());
    }
    ImGui::End();
}

} // namespace px::ed
