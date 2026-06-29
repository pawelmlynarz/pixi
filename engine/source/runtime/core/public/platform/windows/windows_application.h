// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "platform/generic_platform/generic_application.h"

#include <vector>

namespace px {

class GenericWindow;

class WindowsApplication final : public PlatformApplication {
  public:
    void initialize() override;
    void shutdown() override;

    UniquePtr<GenericWindow> createPlatformWindow() override;
    void initializeWindow(SharedRef<GenericWindow> const& window, GenericWindowDefinition const& windowDefinition) override;
    void closeWindow(SharedRef<GenericWindow> const& window) override;

    void pollMessages() override;

  private:
    std::vector<SharedRef<class WindowsWindow>> windows_;
};

struct WindowsApplicationFactory {
    [[nodiscard]]
    static PXENGINE_API UniquePtr<WindowsApplication> create();
};

} // namespace px
