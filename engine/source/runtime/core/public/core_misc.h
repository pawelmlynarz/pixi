// © 2026 Pawel Mlynarz
 
#pragma once

#include "core.h"
#include "common/types.h"

struct PXCORE_API FCoreMisc {
    static void     InitGameThreadId(const uint32 ThreadId);
    
    static uint32   GetGameThreadId();
    static bool     IsInGameThread();
};

