// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "common/types.h"

namespace px {

PXCORE_API void RequestEngineExit();
PXCORE_API bool IsEngineExitRequested();

PXCORE_API bool IsEditor();

PXCORE_API uint32 GetGameThreadId();
PXCORE_API bool IsInGameThread();

} // namespace px
