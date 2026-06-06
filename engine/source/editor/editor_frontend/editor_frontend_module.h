// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_EDITOR_FRONTEND
#define PXEDITOR_FRONTEND_API DLLEXPORT
#else
#define PXEDITOR_FRONTEND_API DLLIMPORT
#endif
#else
#define PXEDITOR_FRONTEND_API
#endif
