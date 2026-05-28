// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_UICORE
#define PXUICORE_API DLLEXPORT
#else
#define PXUICORE_API DLLIMPORT
#endif
#else
#define PXUICORE_API
#endif
