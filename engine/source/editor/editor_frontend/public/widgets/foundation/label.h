// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

struct ImLabelConfig {
    std::string_view Text{"Label"};
    EImFontSize FontSize{EImFontSize::Medium};
};

class ImLabel : public ImWidgetWithConfig<ImLabelConfig>,
                public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed
