//// © 2026 Pawel Mlynarz

#include "widgets/foundation/panel_header.h"
#include "common/alignment.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImPanelHeader::begin() {
    state_.OrygCursorPos_ = ImGui::GetCursorPos();

    ImVec2 const pos{ImGui::GetCursorScreenPos()};
    ImVec2 const avail{ImGui::GetContentRegionAvail()};

    state_.StartX_ = pos.x + Config_.HeaderPadding.x;
    state_.EndX_ = pos.x + avail.x - Config_.HeaderPadding.x;

    state_.CursorXLeft_ = state_.StartX_;
    state_.CursorXRight_ = state_.EndX_;

    state_.CursorXLeft_ = state_.CursorXLeft_ + Config_.FirstWidgetPadding;
    state_.CursorXRight_ = state_.CursorXRight_ - Config_.FirstWidgetPadding;

    state_.Y_ = pos.y + Config_.HeaderPadding.y;

    state_.Gaps_.clear();
}

void ImPanelHeader::addWidget(EWidgetAlignment alignment, IPrecomputedExtentWidget const& widget) {
    addWidget(
        alignment,
        [&]() { return widget.computeExtent(); },
        [&](ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) { widget.drawInExtent(drawList, cursorPos, extent); }
    );
}

void ImPanelHeader::addWidget(
    EWidgetAlignment const alignment, CalculateExtentStrategy const& calculateExtentStrategy, DrawStrategy const& drawStrategy
) {
    ImDrawList* const drawList{ImGui::GetWindowDrawList()};
    ImVec2 const extent{calculateExtentStrategy()};

    if (alignment == EWidgetAlignment::Left) {
        ImGui::SetCursorScreenPos(ImVec2(state_.CursorXLeft_, state_.Y_));

        float const before{state_.CursorXLeft_};
        drawStrategy(drawList, ImVec2(state_.CursorXLeft_, state_.Y_), extent);
        float const after{before + extent.x};

        state_.CursorXLeft_ = after + Config_.NextWidgetPadding;

        state_.Gaps_.emplace_back(before - Config_.GapExtraPadding, after + Config_.GapExtraPadding);
    } else {
        ImGui::SetCursorScreenPos(ImVec2(state_.CursorXRight_ - extent.x, state_.Y_));

        drawStrategy(drawList, ImVec2(state_.CursorXRight_ - extent.x, state_.Y_), extent);
        float const before{state_.CursorXRight_ - extent.x};
        float const after{state_.CursorXRight_};

        state_.CursorXRight_ = before - Config_.NextWidgetPadding;

        state_.Gaps_.emplace_back(before - Config_.GapExtraPadding, after + Config_.GapExtraPadding);
    }
}

void ImPanelHeader::end() const {
    ImDrawList* const dl{ImGui::GetWindowDrawList()};

    ImVec2 const a(state_.StartX_, state_.Y_);
    ImVec2 const b(state_.EndX_, state_.Y_);
    drawDashedLineWithGaps(dl, a, b, state_.Gaps_, Config_.DashLength, Config_.GapLength, Config_.Thickness);

    ImGui::SetCursorPos(state_.OrygCursorPos_);
}

} // namespace px::ed
