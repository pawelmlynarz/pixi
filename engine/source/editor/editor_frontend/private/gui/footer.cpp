// © 2026 Pawel Mlynarz

#include "gui/footer.h"
#include "gui/gui_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImFooter::Draw() {
    ImGui::Begin(NameFooter, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
    }
    ImGui::End();
};

} // namespace px::ed
