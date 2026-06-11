// © 2026 Pawel Mlynarz

#include "widgets/panel_header.h"

#include "imgui/imgui_draw_utils.h"

namespace px::ed {

void ImEditorPanelHeader::Begin(float const PaddingY) {
    StartCursor_ = ImGui::GetCursorScreenPos();
    Y_ = StartCursor_.y + PaddingY;
    Gaps_.clear();
}

void ImEditorPanelHeader::AddWidget(float const WidgetPadding, std::function<void()> WidgetDrawStrategy) {
    ImGui::SameLine();

    float const BeforeX{ImGui::GetCursorScreenPos().x};
    WidgetDrawStrategy();
    Y_ = ImGui::GetItemRectMin().y + ImGui::GetItemRectSize().y * 0.5f;
    float const AfterX{ImGui::GetItemRectMax().x};

    Gaps_.emplace_back(ImVec2(BeforeX - WidgetPadding, AfterX + WidgetPadding));
}

void ImEditorPanelHeader::End(float PaddingX, ImU32 LineColor, float DashLen, float GapLen, float Thickness) const {
    ImVec2 const p0{ImGui::GetWindowPos()};
    ImVec2 const p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y)};

    float const x1{p0.x + PaddingX};
    float const x2{p1.x - PaddingX};

    edimgui::DrawDashedLineWithGaps(
        ImGui::GetWindowDrawList(), ImVec2(x1, Y_), ImVec2(x2, Y_),
        LineColor, DashLen, GapLen, Thickness, Gaps_
    );
}

} // namespace px::ed
