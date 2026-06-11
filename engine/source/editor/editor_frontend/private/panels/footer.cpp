// © 2026 Pawel Mlynarz

#include "panels/footer.h"
#include "editor_const.h"

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
