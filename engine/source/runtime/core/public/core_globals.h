// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "common/types.h"

namespace px {

extern PXCORE_API uint64 gFrameCounter;
extern PXCORE_API uint32 gGameThreadId;
extern PXCORE_API double gStartTime;

PXCORE_API void requestEngineExit();
PXCORE_API bool isEngineExitRequested();

PXCORE_API bool isEditor();

PXCORE_API bool isInGameThread();

} // namespace px
