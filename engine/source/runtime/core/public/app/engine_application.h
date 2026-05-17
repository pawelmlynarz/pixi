// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/utility.h"
#include "tools/misc.h"
#include "window/generic_window_definition.h"

namespace px {

class PlatformApplication;

class EngineApplication final : NonCopyableNonMovable {
  public:
    EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication);
    ~EngineApplication();

    PXCORE_API void Tick();
    PXCORE_API bool AddWindow(GenericWindowDefinition const& WindowDefinition, bool const bShowImmediately) const;

  private:
    SharedRef<PlatformApplication> PlatformApplication_;
};

PXCORE_API bool IsInitialized();
PXCORE_API EngineApplication& GetApplication();

} // namespace px
