// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_RENDERCORE
#define PXRENDERCORE_API DLLEXPORT
#else
#define PXRENDERCORE_API DLLIMPORT
#endif
#else
#define PXRENDERCORE_API
#endif
