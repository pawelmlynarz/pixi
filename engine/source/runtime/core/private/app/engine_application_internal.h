// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"

namespace px {

PXCORE_API void CreateApplication();
PXCORE_API void CreateApplication(SharedRef<class PlatformApplication> const InPlatformApplication);
PXCORE_API void ShutdownApplication();

} // namespace px
