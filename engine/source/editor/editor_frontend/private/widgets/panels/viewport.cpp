// © 2026 Pawel Mlynarz

#include "widgets/panels/viewport.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImViewport::drawPanelContent() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(124, 124));

    drawDashedWindowBorder();
    pushFont(EImFontSize::Large);
    drawDashedHeader("[VIEWPORT]", {24.f, 24.f}, 25);
    popFont();

    ImGui::PopStyleVar();
};

} // namespace px::ed
