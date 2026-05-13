// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_ENGINE
#define PXENGINE_API DLLEXPORT
#else
#define PXENGINE_API DLLIMPORT
#endif
#else
#define PXENGINE_API
#endif
