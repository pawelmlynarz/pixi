// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "platform/generic_platform/generic_application.h"

#include <vector>

namespace px {

class PlatformWindow;

class WindowsApplication final : public PlatformApplication {
  public:
    void initialize() override;
    void shutdown() override;

    UniquePtr<PlatformWindow> createPlatformWindow() override;
    void initializeWindow(SharedRef<PlatformWindow> const& platformWindow, PlatformWindowDefinition const& windowDefinition) override;
    void closeWindow(SharedRef<PlatformWindow> const& platformWindow) override;

    void pollMessages() override;

  private:
    std::vector<SharedRef<class WindowsWindow>> windows_;
};

struct WindowsApplicationFactory {
    [[nodiscard]]
    static PXENGINE_API UniquePtr<WindowsApplication> create();
};

} // namespace px
