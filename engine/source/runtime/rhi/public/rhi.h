// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// NRI
#include "NRI.h"

namespace px {

PX_ENGINE_API void initializeRhi();
PX_ENGINE_API class RHIContext& getRhiContext();
PX_ENGINE_API void shutdownRhi();
PX_ENGINE_API nri::GraphicsAPI getBackend();

} // namespace px
