// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "tools/flags.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

enum class EImInputFieldFlags : uint8 {
    None,
    HasBackground = 1 << 0,
    HasBorder = 1 << 1,
} BitmaskEnum(EImInputFieldFlags);

struct ImInputFieldConfig {
    std::string_view Label{""};
    EImFontSize FontSize{EImFontSize::Medium};
    float Width{300.f};
    EImInputFieldFlags Flags{EImInputFieldFlags::HasBorder};
};

class ImInputField : public ImWidgetWithConfig<ImInputFieldConfig>,
                     public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~IPrecomputedExtentWidget End

    void Draw() const;
};

} // namespace px::ed
