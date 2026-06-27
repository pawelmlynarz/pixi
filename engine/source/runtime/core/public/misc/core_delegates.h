// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/delegates.h"

namespace px {

struct CoreDelegates {
    static PXCORE_API SimpleMulticastDelegate onEngineLoopInitComplete;
    static PXCORE_API SimpleMulticastDelegate onEditorInitComplete;
};

} // namespace px
