// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

class PixiEngine {
  public:
    PX_ENGINE_API void updateTimeAndHandleMaxTickRate();
    PX_ENGINE_API float getDeltaTime() const;
    PX_ENGINE_API float getFps() const;

    struct TimingInfo {
        double CurrentRealTime{0.f};
        float CurrentDeltaTime{0.f};
    } TimingInfo_;
};

PX_ENGINE_API PixiEngine& getEngine();

} // namespace px
