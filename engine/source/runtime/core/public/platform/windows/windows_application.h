// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "platform/generic_platform/generic_application.h"
#include "tools/utility.h"

#include <vector>

namespace px {

class GenericWindow;

class WindowsApplication final : public PlatformApplication {
  public:
    void Initialize() override;
    void Shutdown() override;

    UniquePtr<GenericWindow> CreatePlatformWindow() override;
    void InitializeWindow(SharedRef<GenericWindow> const& Window, GenericWindowDefinition const& WindowDefinition) override;
    void CloseWindow(SharedRef<GenericWindow> const& Window) override;

    void PollMessages() override;

  private:
    std::vector<SharedRef<class WindowsWindow>> Windows_;
};

struct WindowsApplicationFactory {
    [[nodiscard]]
    static PXCORE_API UniquePtr<WindowsApplication> Create();
};

} // namespace px
