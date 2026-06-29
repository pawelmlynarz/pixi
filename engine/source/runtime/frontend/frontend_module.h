// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_ENGINE
#define PXFRONTEND_API DLLEXPORT
#else
#define PXFRONTEND_API DLLIMPORT
#endif
#else
#define PXFRONTEND_API
#endif
