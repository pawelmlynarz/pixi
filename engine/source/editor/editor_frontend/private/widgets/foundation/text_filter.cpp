//// © 2026 Pawel Mlynarz

#include "widgets/foundation/text_filter.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

ImVec2 ImTextFilter::computeExtent() const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    ImVec2 const labelSize{ImGui::CalcTextSize(Config_.Label.data())};

    return {Config_.Width + labelSize.x, labelSize.y};
}

void ImTextFilter::drawInExtent(ImDrawList*, ImVec2, ImVec2 extent) const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - extent.y * .5f);

    int32 pushedStylesCount{0};
    if (!HasFlag(Config_.Flags, EImTextFilterFlags::HasBackground)) {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
        pushedStylesCount += 3;
    }

    if (HasFlag(Config_.Flags, EImTextFilterFlags::HasBorder)) {
        ImGui::PushStyleColor(ImGuiCol_Border, EdStyle::getColorU32(PxGuiCol_FrameBorder));
        pushedStylesCount += 1;
    }

    std::string_view const label{Config_.Label.empty() ? "##Filter" : Config_.Label.data()};
    Config_.TextFilterRef.Draw(label.data(), Config_.Width);

    if (pushedStylesCount > 0) {
        ImGui::PopStyleColor(pushedStylesCount);
    }
}

} // namespace px::ed
