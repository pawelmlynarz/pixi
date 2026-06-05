// © 2026 Pawel Mlynarz

#pragma once

// core
#include "common/types.h"

namespace px {

struct EngineLoop {
    static int32 PreInit();
    static int32 Init();
    static void Tick();
    static void Exit();
};

} // namespace px
