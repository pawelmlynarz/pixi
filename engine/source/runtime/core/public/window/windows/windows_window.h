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

    virtual void InitializeWindow(SharedPtr<PlatformApplication> OwningApplication, GenericWindowDefinition const& WindowDefiinition) override;
    virtual void DestoryWindow() override;

    virtual SharedRef<PlatformApplication> GetOwningApplication() const override;

    virtual void* GetOSWindowHandle() const override;

    PXCORE_API virtual void Show() override;
    PXCORE_API virtual void Hide() override;
    PXCORE_API virtual bool IsVisible() const override;

  private:
    SharedPtr<class WindowsApplication> OwningApplication_{nullptr};
    GenericWindowDefinition Definition_;

    GLFWwindow* Handle_{nullptr};
    HWND Hwnd_{nullptr};
};

struct WindowsWindowFactory {
    static UniquePtr<WindowsWindow> Create();
};

} // namespace px
