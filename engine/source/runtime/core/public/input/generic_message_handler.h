// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "input/key_codes.h"

namespace px {

class PlatformWindow;

class IGenericApplicationMessageHandler {
  public:
    virtual ~IGenericApplicationMessageHandler() = default;

    virtual bool onKeyChar(u32 character, bool isRepeat) = 0;

    virtual bool onKeyDown(i32 keyCode, u32 characterCode, bool isRepeat) = 0;
    virtual bool onKeyUp(i32 keyCode, u32 characterCode, bool isRepeat) = 0;

    virtual bool onMouseDown(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseUp(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseMoved(SharedRef<PlatformWindow> const& platformWindow, Vector2 const& mousePos) = 0;

    virtual void onWindowClose(SharedRef<PlatformWindow> const& platformWindow) = 0;

    virtual void onWindowResized(SharedRef<PlatformWindow> const& platformWindow, u16 width, u16 height, bool wasMinimized) = 0;
};

} // namespace px
