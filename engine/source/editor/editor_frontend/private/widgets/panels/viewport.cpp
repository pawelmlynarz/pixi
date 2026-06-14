// © 2026 Pawel Mlynarz

#include "widgets/panels/viewport.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImViewport::DrawPanelContent() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(124, 124));

    DrawDashedWindowBorder();
    PushFont(EImFontSize::Large);
    DrawDashedHeader("[VIEWPORT]", {24.f, 24.f}, 25);
    PopFont();

    ImGui::PopStyleVar();
};

} // namespace px::ed
