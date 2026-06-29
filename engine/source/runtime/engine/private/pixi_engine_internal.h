// © 2026 Pawel Mlynarz

#pragma once

#include "pixi_engine.h"

namespace px {

[[nodiscard]]
PXENGINE_API int32 initializeEngine(SharedPtr<PixiEngine> const& engine);
PXENGINE_API void destroyEngine();

} // namespace px
