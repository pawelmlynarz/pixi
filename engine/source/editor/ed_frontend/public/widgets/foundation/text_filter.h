// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"
#include "tools/flags.h"

namespace px::ed {

enum class EImTextFilterFlags : uint8 {
    None = 0,
    HasBackground = 1 << 0,
    HasBorder = 1 << 1,
};

struct ImTextFilterConfig {
    ImGuiTextFilter& TextFilterRef;
    std::string_view Label;
    EImFontSize FontSize{EImFontSize::Medium};
    float Width{100.f};
    EImTextFilterFlags Flags{EImTextFilterFlags::HasBorder};
};

class ImTextFilter : public ImWidgetWithConfig<ImTextFilterConfig>,
                     public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 computeExtent() const override;
    void drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const override;

    // ~IPrecomputedExtentWidget End
};

} // namespace px::ed

BitmaskEnum(px::ed::EImTextFilterFlags);
