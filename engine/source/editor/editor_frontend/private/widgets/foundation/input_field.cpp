//// © 2026 Pawel Mlynarz

#include "widgets/foundation/input_field.h"
#include "common/font.h"
#include "styles/editor_style.h"

namespace px::ed {

void ImInputField::draw() const {
    ImVec2 const extent{computeExtent()};
    drawInExtent(nullptr, ImGui::GetCursorPos(), extent);
}

ImVec2 ImInputField::computeExtent() const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};
    ImVec2 const labelSize{ImGui::CalcTextSize(Config_.Label.data())};
    return {labelSize.x + Config_.Width, labelSize.y};
}

void ImInputField::drawInExtent(ImDrawList*, ImVec2, [[maybe_unused]] ImVec2 extent) const {
    ScopeFontOverride const scopeFont{ScopeFontOverride(Config_.FontSize)};

    std::array<char, 256> buf{};

    int32 pushedStylesCount{0};
    if (!HasFlag(Config_.Flags, EImInputFieldFlags::HasBackground)) {
        ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, IM_COL32(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, IM_COL32(0, 0, 0, 0));
        pushedStylesCount += 3;
    }

    if (HasFlag(Config_.Flags, EImInputFieldFlags::HasBorder)) {
        ImGui::PushStyleColor(ImGuiCol_Border, EdStyle::getColorU32(PxGuiCol_FrameBorder));
        pushedStylesCount += 1;
    }
    if (Config_.Width > 0) {
        ImGui::SetNextItemWidth(Config_.Width);
    }
    ImGui::InputText("##", buf.data(), sizeof(buf));

    if (pushedStylesCount > 0) {
        ImGui::PopStyleColor(pushedStylesCount);
    }
}

} // namespace px::ed
