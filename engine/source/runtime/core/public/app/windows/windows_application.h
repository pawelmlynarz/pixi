// © 2026 Pawel Mlynarz

#pragma once

#include "app/platform_application.h"
#include "tools/utility.h"

#include <vector>

namespace px {

class GenericWindow;

class WindowsApplication final : public PlatformApplication {
  public:
    virtual void Initialize() override;
    virtual void Shutdown() override;

    virtual UniquePtr<GenericWindow> CreatePlatformWindow() override;
    virtual void InitializeWindow(SharedRef<GenericWindow> const& Window, GenericWindowDefinition const& WindowDefiinition) override;
    virtual void CloseWindow(SharedRef<GenericWindow> const& Window) override;

    virtual void PollMessages() override;

  private:
    std::vector<SharedRef<class WindowsWindow>> Windows_;
};

struct WindowsApplicationFactory {
    static PXCORE_API UniquePtr<WindowsApplication> Create();
};

} // namespace px
