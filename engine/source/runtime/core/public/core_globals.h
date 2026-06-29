// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

extern PXENGINE_API uint64 gFrameCounter;
extern PXENGINE_API uint32 gGameThreadId;
extern PXENGINE_API double gStartTime;

PXENGINE_API void requestEngineExit();
PXENGINE_API bool isEngineExitRequested();

PXENGINE_API bool isEditor();

PXENGINE_API bool isInGameThread();

} // namespace px
