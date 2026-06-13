//// © 2026 Pawel Mlynarz

#include "widgets/button.h"

namespace px::ed {

ImButton::ImButton(ImButtonConfig const& Config)
    : Config_(Config) {
}

ImVec2 ImButton::ComputeExtent() const {
    edimgui::PushFont(Config_.FontSize);
    ImVec2 const Result{ImGui::CalcTextSize(Config_.Text.data())};
    edimgui::PopFont();
    
    return Result;
}

void ImButton::DrawInExtent(ImDrawList* const DrawList, ImVec2 const CursorPos, ImVec2 const Extent) const {
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - Extent.y * .5f);
    edimgui::PushFont(Config_.FontSize);
    if (edimgui::Button("Clear", Config_.bUnderline)) {
        if (EnsureMsgf(Config_.OnPressed, "Button OnPressed callback not bound.")) {
            Config_.OnPressed();
        }
    }
    edimgui::PopFont();
}

} // namespace px::ed
