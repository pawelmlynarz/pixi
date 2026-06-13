//// © 2026 Pawel Mlynarz

#include "widgets/text_filter.h"
#include "common/formatting.h"

namespace px::ed {

ImTextFilter::ImTextFilter(ImTextFilterConfig const& Config)
    : Config_(Config) {
}

ImVec2 ImTextFilter::ComputeExtent() const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImVec2 const LabelSize{ImGui::CalcTextSize(Config_.Label.data())};

    return ImVec2(Config_.Width + LabelSize.x, LabelSize.y);
}

void ImTextFilter::DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const {
    ScopeFontOverride const ScopeFont{ScopeFontOverride(Config_.FontSize)};
    ImGui::SetCursorPosY(ImGui::GetCursorPos().y - Extent.y * .5f);

    std::string_view const Label{Config_.Label.empty() ? "##Filter" : Config_.Label.data()};
    Config_.TextFilterRef.Draw(Label.data(), Config_.Width);
}

} // namespace px::ed
