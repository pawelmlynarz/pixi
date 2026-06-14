//// © 2026 Pawel Mlynarz

#include "widgets/foundation/label.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

ImVec2 ImLabel::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImLabel::DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    DrawList->AddText(ImVec2(CursorPos.x, CursorPos.y - Extent.y * .5f), EdStyle::GetColorU32(ImGuiCol_Text), Config_.Text.data());
}

} // namespace px::ed
