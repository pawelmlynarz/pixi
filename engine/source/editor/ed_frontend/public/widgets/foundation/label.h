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

    ImVec2 computeExtent() const override;
    void drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed
