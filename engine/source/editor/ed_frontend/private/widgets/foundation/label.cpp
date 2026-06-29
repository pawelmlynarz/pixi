//// © 2026 Pawel Mlynarz

#include "widgets/foundation/label.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

ImVec2 ImLabel::computeExtent() const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImLabel::drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    drawList->AddText(ImVec2(cursorPos.x, cursorPos.y - extent.y * .5f), EdStyle::getColorU32(ImGuiCol_Text), Config_.Text.data());
}

} // namespace px::ed
