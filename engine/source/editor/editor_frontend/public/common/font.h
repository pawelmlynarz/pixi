// © 2026 Pawel Mlynarz

#pragma once

// pxcore
#include "common/types.h"

namespace px::ed {

enum class EImFontSize : uint8 {
    Small,
    Medium,
    Large,
    Max
};

/**
 * Pushes engine font of a predefined size for text rendering.
 */
void PushFont(EImFontSize FontSize);

/**
 * Pops engine font.
 */
void PopFont();

struct ScopeFontOverride {
    ScopeFontOverride(EImFontSize const Size) {
        PushFont(Size);
    }
    ~ScopeFontOverride() {
        PopFont();
    }
};

} // namespace px::ed
