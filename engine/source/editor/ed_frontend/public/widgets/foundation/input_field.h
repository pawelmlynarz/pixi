// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"
#include "common/font.h"
#include "common/bitflags.h"

namespace px::ed {

enum class EImInputFieldFlags : u8 {
    None = 0,
    HasBackground = 1 << 0,
    HasBorder = 1 << 1,
};

PX_ENABLE_BIT_FLAGS(EImInputFieldFlags);

struct ImInputFieldConfig {
    std::string_view Label;
    EImFontSize FontSize{EImFontSize::Medium};
    f32 Width{300.f};
    BitFlags<EImInputFieldFlags> Flags{EImInputFieldFlags::HasBorder};
};

class ImInputField : public ImWidgetWithConfig<ImInputFieldConfig>,
                     public IPrecomputedExtentWidget {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    // ~IPrecomputedExtentWidget Begin

    ImVec2 computeExtent() const override;
    void drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const override;

    // ~IPrecomputedExtentWidget End

    void draw() const;
};

} // namespace px::ed
