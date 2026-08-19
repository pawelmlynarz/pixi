// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

class PixiEngine {
  public:
    PX_ENGINE_API void updateTimeAndHandleMaxTickRate();
    PX_ENGINE_API f32 getDeltaTime() const;
    PX_ENGINE_API f32 getFps() const;

    struct TimingInfo {
        f64 CurrentRealTime{0.f};
        f32 CurrentDeltaTime{0.f};
    } TimingInfo_;
};

PX_ENGINE_API PixiEngine& getEngine();

} // namespace px
