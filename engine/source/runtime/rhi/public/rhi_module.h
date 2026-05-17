// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_RHI
#define PXRHI_API DLLEXPORT
#else
#define PXRHI_API DLLIMPORT
#endif
#else
#define PXRHI_API
#endif
