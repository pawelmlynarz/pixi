// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/delegates.h"

namespace px {

struct CoreDelegates {
    DECLARE_MULTICAST_DELEGATE(FOnEngineLoopInitComplete)
    static PXCORE_API FOnEngineLoopInitComplete onEngineLoopInitComplete;
};

} // namespace px
