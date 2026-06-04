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
        std::string, Title, Title_
    )
    SWIDGET_PROPERTY(
        UVector2, Size, Size_
    )
    SWIDGET_PROPERTY(
        bool, Resizable, Resizable_
    )
    SWIDGET_PROPERTY(
        bool, Decorated, Decorated_
    )

    PXFRONTEND_API void PaintWindow();

    PXFRONTEND_API void SetNativeWindow(WeakPtr<GenericWindow> const& NativeWindow);
    PXFRONTEND_API SharedPtr<GenericWindow> GetNativeWindow() const;
    PXFRONTEND_API void DestoryNativeWindow();

    PXFRONTEND_API void ShowWindow();
    PXFRONTEND_API void HideWindow();

  protected:
    PXFRONTEND_API virtual void DrawImGui() = 0;

  private:
    void RenderImGui_Internal();

    void RenderFrame_Internal();

  private:
    WeakPtr<GenericWindow> NativeWindow_;
    bool bHasEverBeenShown_{false};
    uint32 FrameIdx_{0};
};

} // namespace px
