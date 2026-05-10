// © 2026 Pawel Mlynarz

#pragma once

#include "common/types.h"

namespace px {

struct GenericWindowDefinition {
    uint16 WidthDesired{1280};
    uint16 HeightDesired{720};
    bool bDecorated{true};
    bool bResizable{true};
};

} // namespace px
