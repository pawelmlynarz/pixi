// © 2026 Pawel Mlynarz

#pragma once

#if !defined(PLATFORM_WINDOWS)
#define PLATFORM_WINDOWS 0
#endif

#if PLATFORM_WINDOWS
#include "windows/platform_windows.h"
#endif
