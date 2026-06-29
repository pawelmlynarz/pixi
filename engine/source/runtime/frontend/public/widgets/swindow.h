// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

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

    PXENGINE_API void paintWindow();

    PXENGINE_API void setNativeWindow(WeakPtr<GenericWindow> const& nativeWindow);
    PXENGINE_API SharedPtr<GenericWindow> getNativeWindow() const;
    PXENGINE_API void destoryNativeWindow();

    PXENGINE_API void showWindow();
    PXENGINE_API void hideWindow();

  protected:
    PXENGINE_API virtual void drawImGui() = 0;

  private:
    void renderImGuiInternal();

    void renderFrameInternal();

  private:
    WeakPtr<GenericWindow> nativeWindow_;
    bool bHasEverBeenShown_{false};
    uint32 frameIdx_{0};
};

} // namespace px
