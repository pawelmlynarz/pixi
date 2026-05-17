// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#ifdef PX_BUILD_SHARED
#ifdef PX_BUILD_EDITOR_ENGINE
#define PXEDITOR_ENGINE_API DLLEXPORT
#else
#define PXEDITOR_ENGINE_API DLLIMPORT
#endif
#else
#define PXEDITOR_ENGINE_API
#endif
