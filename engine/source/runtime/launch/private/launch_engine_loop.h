// © 2026 Pawel Mlynarz

#pragma once

// core
#include "common/types.h"

namespace px {

struct EngineLoop {
    static int32 preInit();
    static int32 init();
    static void tick();
    static void exit();
};

} // namespace px
