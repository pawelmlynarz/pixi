// © 2026 Pawel Mlynarz

#pragma once

#include "engine.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

namespace px {

[[nodiscard]]
PXENGINE_API int32 InitializeEngine(SharedPtr<Engine> const& Engine);
PXENGINE_API void DestroyEngine();

} // namespace px
