// © 2026 Pawel Mlynarz

#include "gui/inspector.h"
#include "gui/gui_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImInspector::Draw() {
    ImGui::Begin(NameInspector, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
        edimgui::PushFont(edimgui::EImGuiFontSize::Large);
        edimgui::DrawDashedHeader("[INSPECTOR]", {24.f, 24.f}, 25);
        edimgui::PopFont();
    }
    ImGui::End();
};

} // namespace px::ed
