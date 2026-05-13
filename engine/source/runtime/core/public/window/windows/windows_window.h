// © 2026 Pawel Mlynarz

#pragma once

#include "common/platform.h"
#include "window/generic_window.h"
#include "tools/utility.h"

struct GLFWwindow;

namespace px {

class WindowsWindow final : public GenericWindow {
  public:
    ~WindowsWindow() = default;

    virtual void InitializeWindow(SharedPtr<PlatformApplication> OwningApplication, GenericWindowDefinition const& WindowDefinition) override;
    virtual void DestroyWindow() override;

    virtual SharedRef<PlatformApplication> GetOwningApplication() const override;

    virtual GenericOSWindowHandle GetOSWindowHandle() const override;

    PXCORE_API virtual void Show() override;
    PXCORE_API virtual void Hide() override;
    PXCORE_API virtual bool IsVisible() const override;

  private:
    GLFWwindow* Handle_{nullptr};
    HWND Hwnd_{nullptr};
};

struct WindowsWindowFactory {
    [[nodiscard]]
    static UniquePtr<WindowsWindow> Create();
};

} // namespace px
