// © 2026 Pawel Mlynarz

#include "editor_mainframe.h"

// pxfrontend
#include "pixi_editor_engine.h"

namespace px::ed {

namespace {

ImGuiID CreateDockSpace() {
    ImGuiDockNodeFlags DockspaceFlags{ImGuiDockNodeFlags_PassthruCentralNode};
    ImGuiWindowFlags HostWindowFlags{0};

    HostWindowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoDocking;
    HostWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;

    if (DockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        HostWindowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
    ImGui::Begin("DockSpace Window", nullptr, HostWindowFlags);
    ImGui::PopStyleVar(3);

    ImGuiID const DockspaceID{ImGui::GetID("DockSpace")};
    ImGui::DockSpace(DockspaceID, ImVec2(0.0f, 0.0f), DockspaceFlags, nullptr);
    ImGui::End();

    return DockspaceID;
}

} // namespace

void SEditorMainFrame::DrawImGui() {
    auto& EdEngine{GetEditorEngine()};

    ImGuiViewport* Viewport{ImGui::GetMainViewport()};
    Assert(Viewport != nullptr);
    
    ImGuiID const DockspaceID{CreateDockSpace()};
    
    //ImGui::DockBuilderRemoveNode(DockspaceID);
    //ImGui::DockBuilderAddNode(dockspace_id, ImGuiDockNodeFlags_DockSpace);

    
    ImGui::SetNextWindowDockID(DockspaceID, ImGuiCond_FirstUseEver);
    ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoResize);
    {
        ImGui::Text("FPS: %.2f", EdEngine.GetFPS());
    }
    ImGui::End();
}

} // namespace px::ed
