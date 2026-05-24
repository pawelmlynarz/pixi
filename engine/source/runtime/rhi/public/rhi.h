// © 2026 Pawel Mlynarz

#pragma once

#include "rhi_module.h"

// NRI
#include "NRI.h"

namespace px {

PXRHI_API void InitializeRHI();
PXRHI_API class RHIContext& GetRHIContext();
PXRHI_API void ShutdownRHI();
PXRHI_API nri::GraphicsAPI GetBackend();

} // namespace px
