// © 2026 Pawel Mlynarz

#pragma once

#include "engine_module.h"

namespace px {

class PixiEngine {
  public:
    PXENGINE_API void UpdateTimeAndHandleMaxTickRate();
    PXENGINE_API float GetDeltaTime() const;
    PXENGINE_API float GetFPS() const;
    
    struct TimingInfo {
        double CurrentRealTime{0.f};
        float CurrentDeltaTime{0.f};
    }TimingInfo_;
};

PXENGINE_API PixiEngine& GetEngine();

} // namespace px
