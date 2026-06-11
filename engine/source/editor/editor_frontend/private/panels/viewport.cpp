// © 2026 Pawel Mlynarz

#include "panels/viewport.h"
#include "editor_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImViewport::Draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(124, 124));
    ImGui::Begin(NameViewport, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
        edimgui::PushFont(edimgui::EImGuiFontSize::Large);
        edimgui::DrawDashedHeader("[VIEWPORT]", {24.f, 24.f}, 25);
        edimgui::PopFont();
    }
    ImGui::End();
    ImGui::PopStyleVar();
};

} // namespace px::ed
