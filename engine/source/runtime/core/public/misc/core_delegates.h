// © 2026 Pawel Mlynarz

#pragma once

#include "tools/delegates.h"

namespace px {

struct CoreDelegates {
    DECLARE_MULTICAST_DELEGATE(FOnEngineLoopInitComplete)
    static PXCORE_API FOnEngineLoopInitComplete OnEngineLoopInitComplete;
};

} // namespace px
