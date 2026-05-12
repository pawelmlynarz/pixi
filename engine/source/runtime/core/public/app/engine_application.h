// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/utility.h"
#include "tools/misc.h"
#include "window/generic_window_definition.h"

namespace px {

class PlatformApplication;

class EngineApplication : NonCopyableNonMovable {
  public:
    static PXCORE_API void Create();
    static PXCORE_API void Create(SharedRef<PlatformApplication> const InPlatformApplication);
    static PXCORE_API void Shutdown();

    static PXCORE_API bool IsInitialized();
    static PXCORE_API EngineApplication& Get();

  public:
    EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication);
    ~EngineApplication();

    PXCORE_API bool AddWindow(GenericWindowDefinition const& WindowDefinition, bool const bShowImmediately);

    PXCORE_API void PollMessages();

  private:
    SharedRef<PlatformApplication> PlatformApplication_;
};

} // namespace px
