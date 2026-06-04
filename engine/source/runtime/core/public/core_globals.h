// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "common/types.h"

namespace px {

extern PXCORE_API uint64 GFrameCounter;
extern PXCORE_API uint32 GGameThreadId;
extern PXCORE_API double GStartTime;

PXCORE_API void RequestEngineExit();
PXCORE_API bool IsEngineExitRequested();

PXCORE_API bool IsEditor();

PXCORE_API bool IsInGameThread();

} // namespace px
