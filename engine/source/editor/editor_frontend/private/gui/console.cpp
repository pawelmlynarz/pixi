// © 2026 Pawel Mlynarz

#include "gui/console.h"
#include "gui/gui_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImConsole::Draw() {
    ImGui::Begin(NameConsole, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
        edimgui::PushFont(edimgui::EImGuiFontSize::Large);
        edimgui::DrawDashedHeader("[CONSOLE]", {24.f, 24.f}, 25);
        edimgui::PopFont();
    }
    ImGui::End();
};

} // namespace px::ed
