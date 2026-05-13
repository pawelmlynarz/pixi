// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/utility.h"
#include "tools/misc.h"
#include "window/generic_window_definition.h"

namespace px {

class PlatformApplication;

struct EngineRuntime {
    static PXCORE_API void CreateApplication();
    static PXCORE_API void CreateApplication(SharedRef<PlatformApplication> const InPlatformApplication);
    static PXCORE_API void Shutdown();

    static PXCORE_API bool IsInitialized();
    static PXCORE_API class EngineApplication& GetApplication();
};

class EngineApplication final : NonCopyableNonMovable {
  public:
    EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication);
    ~EngineApplication();

    PXCORE_API bool AddWindow(GenericWindowDefinition const& WindowDefinition, bool const bShowImmediately) const;
    PXCORE_API void PollMessages() const;

  private:
    SharedRef<PlatformApplication> PlatformApplication_;
};

} // namespace px
