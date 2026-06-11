// © 2026 Pawel Mlynarz

#include "panels/scene_hierarchy.h"
#include "editor_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImSceneHierarchy::Draw() {
    ImGui::Begin(NameSceneHierarchy, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
        edimgui::PushFont(edimgui::EImGuiFontSize::Large);
        edimgui::DrawDashedHeader("[SCENE HIERARCHY]", {24.f, 24.f}, 25);
        edimgui::PopFont();
    }
    ImGui::End();
};

} // namespace px::ed
