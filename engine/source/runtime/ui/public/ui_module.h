// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_UI
#define PXUI_API DLLEXPORT
#else
#define PXUI_API DLLIMPORT
#endif
#else
#define PXUI_API
#endif
