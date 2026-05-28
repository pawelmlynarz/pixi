// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_RENDERER
#define PXRENDERER_API DLLEXPORT
#else
#define PXRENDERER_API DLLIMPORT
#endif
#else
#define PXRENDERER_API
#endif
