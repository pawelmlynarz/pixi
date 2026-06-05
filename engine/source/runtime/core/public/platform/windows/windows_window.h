// © 2026 Pawel Mlynarz

#pragma once

#include "platform/generic_platform/generic_window.h"
#include "tools/utility.h"

struct GLFWwindow;

#ifndef HWND_DEFINED
// NOLINTNEXTLINE(modernize-use-using)
typedef struct HWND__* HWND;
#define HWND_DEFINED
#endif

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
