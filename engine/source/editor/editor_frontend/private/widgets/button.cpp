//// © 2026 Pawel Mlynarz

#include "widgets/button.h"
#include "common/formatting.h"

namespace px::ed {

ImButton::ImButton(ImButtonConfig const& Config)
    : Config_(Config) {
}

ImVec2 ImButton::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImButton::DrawInExtent(ImDrawList* const DrawList, ImVec2 const CursorPos, ImVec2 const Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - Extent.y * .5f);

    if (edimgui::Button("Clear", Config_.bUnderline)) {
        if (EnsureMsgf(Config_.OnPressed, "Button OnPressed callback not bound.")) {
            Config_.OnPressed();
        }
    }
}

} // namespace px::ed
