// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/utility.h"

namespace px {

class PlatformApplication;

class EngineApplication {
  public:
    static PXCORE_API void Create();
    static PXCORE_API void Create(SharedRef<PlatformApplication> const InPlatformApplication);
    static PXCORE_API void Shutdown();

  public:
    EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication);

  private:
    SharedRef<PlatformApplication> PlatformApplication_;
};

} // namespace px
