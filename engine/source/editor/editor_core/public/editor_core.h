// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_EDITOR_CORE
#define PXEDITOR_CORE_API DLLEXPORT
#else
#define PXEDITOR_CORE_API DLLIMPORT
#endif
#else
#define PXEDITOR_CORE_API
#endif
