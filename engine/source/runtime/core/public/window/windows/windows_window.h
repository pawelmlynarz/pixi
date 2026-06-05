// © 2026 Pawel Mlynarz

#pragma once

#include "common/platform.h"
#include "window/generic_window.h"
#include "tools/utility.h"

struct GLFWwindow;

namespace px {

class WindowsWindow final : public GenericWindow {
  public:
    ~WindowsWindow() override = default;

    void InitializeWindow(SharedPtr<PlatformApplication> OwningApplication, GenericWindowDefinition const& WindowDefinition) override;
    void DestroyWindow() override;

    SharedRef<PlatformApplication> GetOwningApplication() const override;

    GenericOSWindowHandle GetOSWindowHandle() const override;

    PXCORE_API void Show() override;
    PXCORE_API void Hide() override;
    PXCORE_API bool IsVisible() const override;

  private:
    GLFWwindow* Handle_{nullptr};
    HWND Hwnd_{nullptr};
};

struct WindowsWindowFactory {
    [[nodiscard]]
    static UniquePtr<WindowsWindow> Create();
};

} // namespace px
