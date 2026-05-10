// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/utility.h"
#include "window/generic_window_definition.h"

namespace px {

class PlatformApplication {
  public:
    virtual ~PlatformApplication() = default;

    virtual UniquePtr<class GenericWindow> CreatePlatformWindow();
    virtual void InitializeWindow([[maybe_unused]] SharedRef<GenericWindow> const& Window, [[maybe_unused]] GenericWindowDefinition const& WindowDefiinition) {};
};

} // namespace px
