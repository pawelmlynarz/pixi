//// © 2026 Pawel Mlynarz

#include "widgets/foundation/button.h"
#include "common/font.h"
#include "styles/editor_style.h"
#include "utils/imgui_draw_utils.h"

// imgui
#include "imgui_internal.h"

namespace px::ed {

bool imButtonNative(std::string_view label, bool bUnderline) {
    ImGuiWindow* const window{ImGui::GetCurrentWindow()};

    if (window->SkipItems) {
        return false;
    }
    ImGuiID const id{window->GetID(cStr(label))};

    ImVec2 const textSize{ImGui::CalcTextSize(cStr(label))};
    ImVec2 const pos{ImGui::GetCursorScreenPos()};
    ImRect const bb(pos, ImVec2(pos.x + textSize.x, pos.y + textSize.y));

    ImGui::ItemSize(bb);
    if (!ImGui::ItemAdd(bb, id)) {
        return false;
    }
    bool const bHovered{ImGui::ItemHoverable(bb, id, 0)};
    bool const bClicked{bHovered && ImGui::IsMouseReleased(0)};
    bool const bPressed{bHovered && ImGui::IsMouseDown(0)};

    ImU32 textColor{EdStyle::getColorU32(PxGuiCol_Text)};
    if (bPressed) {
        textColor = EdStyle::getColorU32(PxGuiCol_TextActive);
    } else if (bHovered) {
        textColor = EdStyle::getColorU32(PxGuiCol_TextHovered);
    }
    window->DrawList->AddText(pos, textColor, cStr(label));

    if (bUnderline) {
        ImVec2 const underlineStart(pos.x, pos.y + textSize.y);
        ImVec2 const underlineEnd(pos.x + textSize.x, pos.y + textSize.y);

        window->DrawList->AddLine(underlineStart, underlineEnd, textColor, 1.f);
    }
    return bClicked;
}

ImVec2 ImButton::computeExtent() const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    return ImGui::CalcTextSize(Config_.Text.data());
}

void ImButton::drawInExtent(ImDrawList* const, ImVec2 const, ImVec2 const extent) const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - extent.y * .5f);

    if (imButtonNative("Clear", Config_.bUnderline)) {
        if (pxEnsureMsgf(Config_.OnPressed, "Button OnPressed callback not bound.")) {
            Config_.OnPressed();
        }
    }
}

} // namespace px::ed
