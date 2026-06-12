//// © 2026 Pawel Mlynarz

#include "widgets/panel_header.h"

#include "imgui/imgui_draw_utils.h"

namespace px::ed {

void ImEditorPanelHeader::Begin(ImEditorPanelHeaderConfig const& Config) {
    Config_ = Config;
    State_.OrygCursorPos_ = ImGui::GetCursorPos();

    ImVec2 const Pos{ImGui::GetCursorScreenPos()};
    ImVec2 const Avail{ImGui::GetContentRegionAvail()};

    State_.StartX_ = Pos.x + Config_.HeaderPadding.x;
    State_.EndX_ = Pos.x + Avail.x - Config_.HeaderPadding.x;

    State_.CursorXLeft_ = State_.StartX_;
    State_.CursorXRight_ = State_.EndX_;

    State_.CursorXLeft_ = State_.CursorXLeft_ + Config_.FirstWidgetPadding;
    State_.CursorXRight_ = State_.CursorXRight_ - Config_.FirstWidgetPadding;

    State_.Y_ = Pos.y + Config_.HeaderPadding.y;

    State_.Gaps_.clear();
}

void ImEditorPanelHeader::AddWidget(
    EEditorPanelHeaderItemAlignment const Alignment, CalculateExtentStrategy const& CalculateExtentStrategy, DrawStrategy const& DrawStrategy
) {
    ImDrawList* const DrawList{ImGui::GetWindowDrawList()};
    ImVec2 const Extent{CalculateExtentStrategy()};

    if (Alignment == EEditorPanelHeaderItemAlignment::Left) {
        ImGui::SetCursorScreenPos(ImVec2(State_.CursorXLeft_, State_.Y_));

        float const Before{State_.CursorXLeft_};
        DrawStrategy(DrawList, ImVec2(State_.CursorXLeft_, State_.Y_), Extent);
        float const After{Before + Extent.x};

        State_.CursorXLeft_ = After + Config_.NextWidgetPadding;

        State_.Gaps_.emplace_back(Before - Config_.GapExtraPadding, After + Config_.GapExtraPadding);
    } else {
        ImGui::SetCursorScreenPos(ImVec2(State_.CursorXRight_ - Extent.x, State_.Y_));

        DrawStrategy(DrawList, ImVec2(State_.CursorXRight_ - Extent.x, State_.Y_), Extent);
        float const Before{State_.CursorXRight_ - Extent.x};
        float const After{State_.CursorXRight_};

        State_.CursorXRight_ = Before - Config_.NextWidgetPadding;

        State_.Gaps_.emplace_back(Before - Config_.GapExtraPadding, After + Config_.GapExtraPadding);
    }
}

void ImEditorPanelHeader::End() const {
    ImDrawList* const dl{ImGui::GetWindowDrawList()};

    ImVec2 const a(State_.StartX_, State_.Y_);
    ImVec2 const b(State_.EndX_, State_.Y_);
    edimgui::DrawDashedLineWithGaps(dl, a, b, State_.Gaps_, Config_.LineColor, Config_.DashLength, Config_.GapLength, Config_.Thickness);

    ImGui::SetCursorPos(State_.OrygCursorPos_);
}

} // namespace px::ed
