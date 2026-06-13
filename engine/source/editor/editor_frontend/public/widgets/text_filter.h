// © 2026 Pawel Mlynarz

#pragma once

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_widget.h"

namespace px::ed {

struct ImTextFilterConfig {
    ImGuiTextFilter& TextFilterRef;
    std::string_view Label{""};
    edimgui::EImGuiFontSize FontSize{edimgui::EImGuiFontSize::Medium};
    float Width{100.f};
};

class ImTextFilter : public ImPrecomputedExtentWidget {
  public:
    ImTextFilter(ImTextFilterConfig const& Config);

    // ~ImPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~ImPrecomputedExtentWidget End

  private:
    ImTextFilterConfig Config_;
};

} // namespace px::ed
