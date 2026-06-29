// © 2026 Pawel Mlynarz

#pragma once

#include "common/callback_defs.h"
#include "widgets/widget.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

struct ImButtonConfig {
    std::string_view Text{"Button"};
    EImFontSize FontSize{EImFontSize::Medium};

    bool bUnderline{false};

    ButtonPressedCallback OnPressed;
};

bool imButtonNative(std::string_view label, bool bUnderline);

class ImButton
    : public ImWidgetWithConfig<ImButtonConfig>,
      public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 computeExtent() const override;
    void drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed
