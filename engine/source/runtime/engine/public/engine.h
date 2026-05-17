// © 2026 Pawel Mlynarz

#pragma once

#include "engine_module.h"

// pxcore
#include "tools/utility.h"

namespace px {

class Engine {
};

PXENGINE_API void InitializeEngine(SharedPtr<Engine> const& Engine);
PXENGINE_API void DestroyEngine();
PXENGINE_API SharedRef<Engine> GetEngine();

} // namespace px
