// © 2026 Pawel Mlynarz

#pragma once

#include "pixi_engine.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

namespace px {

[[nodiscard]]
PXENGINE_API int32 initializeEngine(SharedPtr<PixiEngine> const& engine);
PXENGINE_API void destroyEngine();

} // namespace px
