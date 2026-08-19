// © 2026 Pawel Mlynarz

#pragma once

// pxEngine
#include "common/types.h"

namespace px {

struct EngineLoop {
    static i32 preInit();
    static i32 init();
    static void tick();
    static void exit();
};

} // namespace px
