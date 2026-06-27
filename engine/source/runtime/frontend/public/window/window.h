// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"

// pxcore
#include "tools/utility.h"
#include "common/types.h"

#include <string>

namespace px {

class PlatformWindow;

class Window : public EnableSharedFromThis<Window> {
  public:
    virtual ~Window() = default;

    UVector2 const& getSize() const { return size_; }
    Window& size(UVector2 const& size) {
        size_ = size;
        return *this;
    }

    std::string_view getTitle() const { return title_; }
    Window& title(std::string const& title) {
        title_ = title;
        return *this;
    }

    bool getResizable() const { return resizable_; }
    Window& resizable(bool const resizable) {
        resizable_ = resizable;
        return *this;
    }

    bool getDecorated() const { return decorated_; }
    Window& decorated(bool const decorated) {
        decorated_ = decorated;
        return *this;
    }

    PXFRONTEND_API void paintWindow();

    PXFRONTEND_API void setNativeWindow(WeakPtr<PlatformWindow> const& platformWindow);
    PXFRONTEND_API SharedPtr<PlatformWindow> getNativeWindow() const;
    PXFRONTEND_API void destoryNativeWindow();

    PXFRONTEND_API void showWindow();
    PXFRONTEND_API void hideWindow();

  protected:
#if WITH_IMGUI
    PXFRONTEND_API virtual void drawImGui() = 0;
#endif

  private:
    std::string title_;
    UVector2 size_;
    bool resizable_{false};
    bool decorated_{false};

  private:
    void renderImGuiInternal();

    void renderFrameInternal();

  private:
    WeakPtr<PlatformWindow> nativeWindow_;
    bool bHasEverBeenShown_{false};
    uint32 frameIdx_{0};
};

} // namespace px
