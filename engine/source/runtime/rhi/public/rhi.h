// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// NRI
#include "NRI.h"

namespace px {

PXENGINE_API void initializeRhi();
PXENGINE_API class RHIContext& getRhiContext();
PXENGINE_API void shutdownRhi();
PXENGINE_API nri::GraphicsAPI getBackend();

} // namespace px
