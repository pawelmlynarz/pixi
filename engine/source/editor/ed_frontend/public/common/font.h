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
void pushFont(EImFontSize fontSize);

/**
 * Pops engine font.
 */
void popFont();

struct ScopeFontOverride {
    ScopeFontOverride(EImFontSize const size) {
        pushFont(size);
    }
    ~ScopeFontOverride() {
        popFont();
    }
};

} // namespace px::ed
