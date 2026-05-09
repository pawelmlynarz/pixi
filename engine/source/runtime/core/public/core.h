// © 2026 Pawel Mlynarz

#pragma once

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_CORE
#define PXCORE_API DLLEXPORT
#else
#define PXCORE_API DLLIMPORT
#endif
#else
#define PXCORE_API
#endif

#include "platform.h"
#include "core_types.h"
