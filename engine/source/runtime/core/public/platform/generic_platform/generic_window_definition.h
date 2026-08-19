// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

#include <string_view>

namespace px {

struct PlatformWindowDefinition {
    std::string_view title;
    u16 widthDesired{1280};
    u16 heightDesired{720};
    bool decorated{true};
    bool resizable{true};
};

} // namespace px
