// © 2026 Pawel Mlynarz

#pragma once

#include "pixi_engine.h"

namespace px {

[[nodiscard]]
PX_ENGINE_API i32 initializeEngine(SharedPtr<PixiEngine> const& engine);
PX_ENGINE_API void destroyEngine();

} // namespace px
