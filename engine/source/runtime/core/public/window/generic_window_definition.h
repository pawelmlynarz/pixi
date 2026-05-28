// © 2026 Pawel Mlynarz

#pragma once

#include "common/types.h"

#include <string_view>

namespace px {

struct GenericWindowDefinition {
    std::string_view Title;
    uint16 WidthDesired{1280};
    uint16 HeightDesired{720};
    bool bDecorated{true};
    bool bResizable{true};
};

} // namespace px
