// © 2026 Pawel Mlynarz

#pragma once

#include "uicore_module.h"
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
        std::string, Title, Title_)
    SWIDGET_PROPERTY(
        UVector2, Size, Size_)
    SWIDGET_PROPERTY(
        bool, Resizable, Resizable_)
    SWIDGET_PROPERTY(
        bool, Decorated, Decorated_)
    
    PXUICORE_API virtual void Draw() = 0;
    
    PXUICORE_API void SetNativeWindow(WeakPtr<GenericWindow> const& NativeWindow);
    PXUICORE_API SharedPtr<GenericWindow> GetNativeWindow() const;
    PXUICORE_API void DestoryNativeWindow();

    PXUICORE_API void ShowWindow();
    PXUICORE_API void HideWindow();
    
  private:
    WeakPtr<GenericWindow> NativeWindow_;
    bool bHasEverBeenShown_{false};
};

} // namespace px
