//// © 2026 Pawel Mlynarz

#include "widgets/foundation/button.h"
#include "common/font.h"
#include "styles/editor_style.h"
#include "utils/imgui_draw_utils.h"

// imgui
#include "imgui_internal.h"

namespace px::ed {

bool ImButtonNative(std::string_view Label, bool bUnderline) {
    ImGuiWindow* const Window{ImGui::GetCurrentWindow()};

    if (Window->SkipItems) {
        return false;
    }
    ImGuiID const ID{Window->GetID(CStr(Label))};

    ImVec2 const TextSize{ImGui::CalcTextSize(CStr(Label))};
    ImVec2 const Pos{ImGui::GetCursorScreenPos()};
    ImRect const BB(Pos, ImVec2(Pos.x + TextSize.x, Pos.y + TextSize.y));

    ImGui::ItemSize(BB);
    if (!ImGui::ItemAdd(BB, ID)) {
        return false;
    }
    bool const bHovered{ImGui::ItemHoverable(BB, ID, 0)};
    bool const bClicked{bHovered && ImGui::IsMouseReleased(0)};
    bool const bPressed{bHovered && ImGui::IsMouseDown(0)};

    ImU32 TextColor{EdStyle::GetColorU32(PxGuiCol_Text)};
    if (bPressed) {
        TextColor = EdStyle::GetColorU32(PxGuiCol_TextActive);
    } else if (bHovered) {
        TextColor = EdStyle::GetColorU32(PxGuiCol_TextHovered);
    }
    Window->DrawList->AddText(Pos, TextColor, CStr(Label));

    if (bUnderline) {
        ImVec2 const UnderlineStart(Pos.x, Pos.y + TextSize.y);
        ImVec2 const UnderlineEnd(Pos.x + TextSize.x, Pos.y + TextSize.y);

        Window->DrawList->AddLine(UnderlineStart, UnderlineEnd, TextColor, 1.f);
    }
    return bClicked;
}

ImVec2 ImButton::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImButton::DrawInExtent(ImDrawList* const, ImVec2 const, ImVec2 const Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - Extent.y * .5f);

    if (ImButtonNative("Clear", Config_.bUnderline)) {
        if (EnsureMsgf(Config_.OnPressed, "Button OnPressed callback not bound.")) {
            Config_.OnPressed();
        }
    }
}

} // namespace px::ed
