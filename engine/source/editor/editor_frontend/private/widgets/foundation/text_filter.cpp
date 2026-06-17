//// © 2026 Pawel Mlynarz

#include "widgets/foundation/text_filter.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

ImVec2 ImTextFilter::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImVec2 const LabelSize{ImGui::CalcTextSize(Config_.Label.data())};

    return {Config_.Width + LabelSize.x, LabelSize.y};
}

void ImTextFilter::DrawInExtent(ImDrawList*, ImVec2, ImVec2 Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - Extent.y * .5f);

    int32 PushedStylesCount{0};
    if (!HasFlag(Config_.Flags, EImTextFilterFlags::HasBackground)) {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
        PushedStylesCount += 3;
    }

    if (HasFlag(Config_.Flags, EImTextFilterFlags::HasBorder)) {
        ImGui::PushStyleColor(ImGuiCol_Border, EdStyle::GetColorU32(PxGuiCol_FrameBorder));
        PushedStylesCount += 1;
    }

    std::string_view const Label{Config_.Label.empty() ? "##Filter" : Config_.Label.data()};
    Config_.TextFilterRef.Draw(Label.data(), Config_.Width);

    if (PushedStylesCount > 0) {
        ImGui::PopStyleColor(PushedStylesCount);
    }
}

} // namespace px::ed
