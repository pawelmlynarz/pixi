// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

extern PX_ENGINE_API uint64 gFrameCounter;
extern PX_ENGINE_API uint32 gGameThreadId;
extern PX_ENGINE_API double gStartTime;

PX_ENGINE_API void requestEngineExit();
PX_ENGINE_API bool isEngineExitRequested();

PX_ENGINE_API bool isEditor();

PX_ENGINE_API bool isInGameThread();

} // namespace px
