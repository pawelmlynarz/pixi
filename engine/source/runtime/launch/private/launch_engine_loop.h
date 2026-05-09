// © 2026 Pawel Mlynarz

#pragma once

// core
#include "common/types.h"

namespace px {

struct EngineLoop {
    int32 PreInit();
    int32 Init();
    void Tick();
    void Exit();
};

extern EngineLoop GEngineLoop;

} // namespace px
