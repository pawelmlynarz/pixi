// © 2026 Pawel Mlynarz

#pragma once

#include "common/types.h"

#include <string_view>

namespace px {

struct PlatformWindowDefinition {
    std::string_view title;
    uint16 widthDesired{1280};
    uint16 heightDesired{720};
    bool decorated{true};
    bool resizable{true};
};

} // namespace px
