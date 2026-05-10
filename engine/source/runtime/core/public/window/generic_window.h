// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/misc.h"
#include "generic_window_definition.h"

namespace px {

class GenericWindow : NonCopyableNonMovable {
  public:
    virtual ~GenericWindow() = default;

  public:
    virtual void InitializeWindow([[maybe_unused]] GenericWindowDefinition const& WindowDefiinition) {}
    virtual void DestoryWindow() {};

    [[nodiscard]]
    virtual void* GetOSWindowHandle() const { return nullptr; };

    PXCORE_API virtual void Show() {};
    PXCORE_API virtual void Hide() {};
    PXCORE_API virtual bool IsVisible() const { return false; };
};

} // namespace px
