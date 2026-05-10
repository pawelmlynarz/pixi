// © 2026 Pawel Mlynarz

#pragma once

#include "app/platform_application.h"
#include "tools/utility.h"

#include <vector>

namespace px {

class GenericWindow;

class WindowsApplication final : public PlatformApplication {
  public:
    virtual UniquePtr<GenericWindow> CreatePlatformWindow() override;
    virtual void InitializeWindow(SharedRef<GenericWindow> const& Window, GenericWindowDefinition const& WindowDefiinition) override;

  private:
    std::vector<SharedRef<class WindowsWindow>> Windows_;
};

struct WindowsApplicationFactory {
    static PXCORE_API UniquePtr<WindowsApplication> Create();
};

} // namespace px
