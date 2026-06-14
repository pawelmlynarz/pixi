// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

struct ImTextFilterConfig {
    ImGuiTextFilter& TextFilterRef;
    std::string_view Label{""};
    EImFontSize FontSize{EImFontSize::Medium};
    float Width{100.f};
};

class ImTextFilter : public ImWidgetWithConfig<ImTextFilterConfig>,
                     public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed
