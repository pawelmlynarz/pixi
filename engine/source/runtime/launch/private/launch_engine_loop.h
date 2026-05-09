// © 2026 Pawel Mlynarz

#pragma once

#include "common/types.h"

namespace px {
class EngineLoop {
public:
    int32 PreInit();
    int32 Init();
    void Tick();
    void Exit();
}; 

extern EngineLoop GEngineLoop;
}
