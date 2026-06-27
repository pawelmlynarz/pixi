// © 2026 Pawel Mlynarz

#pragma once

#include "rhi_module.h"

// NRI
#include "NRI.h"

namespace px {

PXRHI_API void initializeRhi();
PXRHI_API class RHIContext& getRhiContext();
PXRHI_API void shutdownRhi();
PXRHI_API nri::GraphicsAPI getBackend();

} // namespace px
