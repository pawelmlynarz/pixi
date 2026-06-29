// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/delegates.h"

namespace px {

struct CoreDelegates {
    static PXENGINE_API SimpleMulticastDelegate onEngineLoopInitComplete;
    static PXENGINE_API SimpleMulticastDelegate onEditorInitComplete;
};

} // namespace px
