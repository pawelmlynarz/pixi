// © 2026 Pawel Mlynarz

#pragma once

#include "imgui/imgui_draw_utils.h"

namespace px::ed {

enum class EWidgetAlignment : uint8 {
    Left,
    Right
};

struct ScopeFontOverride {
    ScopeFontOverride(edimgui::EImGuiFontSize const Size) {
        edimgui::PushFont(Size);
    }
    ~ScopeFontOverride() {
        edimgui::PopFont();
    }
};

} // namespace px::ed
