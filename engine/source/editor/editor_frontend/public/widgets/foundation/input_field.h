// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "tools/flags.h"

namespace px::ed {

enum class EImInputFieldFlags : uint8 {
    None = 0,
    HasBackground = 1 << 0,
    HasBorder = 1 << 1,
};

struct ImInputFieldConfig {
    std::string_view Label;
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

BitmaskEnum(px::ed::EImInputFieldFlags);
