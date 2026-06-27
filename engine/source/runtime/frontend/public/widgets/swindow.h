// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"
#include "swidget.h"

// pxcore
#include "tools/utility.h"
#include "common/types.h"

#include <string>

namespace px {

class GenericWindow;

class SWindow : public SWidget {
  public:
    SWIDGET_PROPERTY(
        std::string, Title
    )
    SWIDGET_PROPERTY(
        UVector2, Size
    )
    SWIDGET_PROPERTY(
        bool, Resizable
    )
    SWIDGET_PROPERTY(
        bool, Decorated
    )

    PXFRONTEND_API void paintWindow();

    PXFRONTEND_API void setNativeWindow(WeakPtr<GenericWindow> const& nativeWindow);
    PXFRONTEND_API SharedPtr<GenericWindow> getNativeWindow() const;
    PXFRONTEND_API void destoryNativeWindow();

    PXFRONTEND_API void showWindow();
    PXFRONTEND_API void hideWindow();

  protected:
    PXFRONTEND_API virtual void drawImGui() = 0;

  private:
    void renderImGuiInternal();

    void renderFrameInternal();

  private:
    WeakPtr<GenericWindow> nativeWindow_;
    bool bHasEverBeenShown_{false};
    uint32 frameIdx_{0};
};

} // namespace px
