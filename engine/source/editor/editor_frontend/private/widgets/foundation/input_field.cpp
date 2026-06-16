//// © 2026 Pawel Mlynarz

#include "widgets/foundation/input_field.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

void ImInputField::Draw() const {
    ImVec2 const Extent{ComputeExtent()};
    DrawInExtent(nullptr, ImGui::GetCursorPos(), Extent);
}

ImVec2 ImInputField::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImVec2 const LabelSize{ImGui::CalcTextSize(Config_.Label.data())};
    return {LabelSize.x + Config_.Width, LabelSize.y};
}

void ImInputField::DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};

    char Buf[256] = "";

    int32 PushedStylesCount{0};
    if (!HasFlag(Config_.Flags, EImInputFieldFlags::HasBackground)) {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
        PushedStylesCount += 3;
    }

    if (HasFlag(Config_.Flags, EImInputFieldFlags::HasBorder)) {
        ImGui::PushStyleColor(ImGuiCol_Border, EdStyle::GetColorU32(PxGuiCol_FrameBorder));
        PushedStylesCount += 1;
    }
    if (Config_.Width > 0) {
        ImGui::SetNextItemWidth(Config_.Width);
    }
    ImGui::InputText("##", Buf, sizeof(Buf));

    if (PushedStylesCount > 0) {
        ImGui::PopStyleColor(PushedStylesCount);
    }
}

} // namespace px::ed
