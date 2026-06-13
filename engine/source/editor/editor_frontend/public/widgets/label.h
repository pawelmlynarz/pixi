// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_widget.h"

namespace px::ed {

struct ImLabelConfig {
    std::string_view Text{"Label"};
    edimgui::EImGuiFontSize FontSize{edimgui::EImGuiFontSize::Medium};
    ImU32 Color{IM_COL32(220, 220, 220, 255)};
};

class ImLabel : public ImPrecomputedExtentWidget {
  public:
    ImLabel(ImLabelConfig const& Config);

    // ~ImPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~ImPrecomputedExtentWidget End

  private:
    ImLabelConfig Config_;
};

} // namespace px::ed
