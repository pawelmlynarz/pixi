// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/delegates.h"

namespace px {

struct CoreDelegates {
    static PX_ENGINE_API SimpleMulticastDelegate onEngineLoopInitComplete;
    static PX_ENGINE_API SimpleMulticastDelegate onEditorInitComplete;
};

} // namespace px
