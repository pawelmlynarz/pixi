// © 2026 Pawel Mlynarz

#pragma once

#include "engine_module.h"

namespace px {

class PixiEngine {
  public:
    PXENGINE_API void updateTimeAndHandleMaxTickRate();
    PXENGINE_API float getDeltaTime() const;
    PXENGINE_API float getFps() const;

    struct TimingInfo {
        double CurrentRealTime{0.f};
        float CurrentDeltaTime{0.f};
    } TimingInfo_;
};

PXENGINE_API PixiEngine& getEngine();

} // namespace px
