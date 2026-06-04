// © 2026 Pawel Mlynarz

#pragma once

#include "engine_module.h"

namespace px {

class PixiEngine {
  public:
    PXENGINE_API void UpdateTimeAndHandleMaxTickRate();
    PXENGINE_API float GetDeltaTime() const;
    PXENGINE_API float GetFPS() const;
};

PXENGINE_API PixiEngine& GetEngine();

} // namespace px
