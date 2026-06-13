//// © 2026 Pawel Mlynarz

#include "widgets/label.h"
#include "common/formatting.h"

namespace px::ed {

ImLabel::ImLabel(ImLabelConfig const& Config)
    : Config_(Config) {
}

ImVec2 ImLabel::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImLabel::DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    DrawList->AddText(ImVec2(CursorPos.x, CursorPos.y - Extent.y * .5f), IM_COL32(220, 220, 220, 255), Config_.Text.data());
}

} // namespace px::ed
