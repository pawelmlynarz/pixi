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

bool ImButtonNative(std::string_view Label, bool bUnderline);

class ImButton
    : public ImWidgetWithConfig<ImButtonConfig>,
      public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed
