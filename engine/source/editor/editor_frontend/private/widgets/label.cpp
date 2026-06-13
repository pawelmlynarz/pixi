//// © 2026 Pawel Mlynarz

#include "widgets/label.h"

namespace px::ed {

ImLabel::ImLabel(ImLabelConfig const& Config)
    : Config_(Config) {
}

ImVec2 ImLabel::ComputeExtent() const {
    edimgui::PushFont(Config_.FontSize);
    ImVec2 const Result{ImGui::CalcTextSize(Config_.Text.data())};
    edimgui::PopFont();

    return Result;
}

void ImLabel::DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const {
    edimgui::PushFont(Config_.FontSize);
    DrawList->AddText(ImVec2(CursorPos.x, CursorPos.y - Extent.y * .5f), IM_COL32(220, 220, 220, 255), Config_.Text.data());
    edimgui::PopFont();
}

} // namespace px::ed
