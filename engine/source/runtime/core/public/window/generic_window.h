// © 2026 Pawel Mlynarz

#pragma once

#include "tools/misc.h"

namespace px {

class GenericWindow : NonCopyableNonMovable {
    virtual ~GenericWindow() = default;
    
public:
    [[nodiscard]]
    virtual void* GetOSWindowHandle() const = 0;
};

} // namespace px
