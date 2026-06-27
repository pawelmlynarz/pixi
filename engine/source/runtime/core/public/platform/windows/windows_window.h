// © 2026 Pawel Mlynarz

#pragma once

#include "platform/generic_platform/generic_window.h"
#include "tools/utility.h"

struct GLFWwindow;

#ifndef HWND_DEFINED
// NOLINTNEXTLINE(*)
typedef struct HWND__* HWND;
#define HWND_DEFINED
#endif

namespace px {

class WindowsWindow final : public PlatformWindow {
  public:
    ~WindowsWindow() override = default;

    void initializeWindow(SharedPtr<PlatformApplication> owningApplication, PlatformWindowDefinition const& windowDefinition) override;
    void destroyWindow() override;

    SharedRef<PlatformApplication> getOwningApplication() const override;

    GenericOSWindowHandle getOsWindowHandle() const override;

    PXCORE_API void show() override;
    PXCORE_API void hide() override;
    PXCORE_API bool isVisible() const override;
    PXCORE_API bool isFullscreenSupported() const override;

  private:
    GLFWwindow* handle_{nullptr};
    HWND hwnd_{nullptr};
};

struct WindowsWindowFactory {
    [[nodiscard]]
    static UniquePtr<WindowsWindow> create();
};

} // namespace px
