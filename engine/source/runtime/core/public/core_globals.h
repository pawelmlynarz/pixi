// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

extern PX_ENGINE_API u64 gFrameCounter;
extern PX_ENGINE_API u32 gGameThreadId;
extern PX_ENGINE_API f64 gStartTime;

PX_ENGINE_API void requestEngineExit();

PX_ENGINE_API bool isEngineExitRequested();

PX_ENGINE_API bool isEditor();

PX_ENGINE_API bool isInGameThread();

} // namespace px
