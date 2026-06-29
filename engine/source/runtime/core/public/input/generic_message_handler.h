// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "input/key_codes.h"

namespace px {

class PlatformWindow;

class IGenericApplicationMessageHandler {
  public:
    virtual ~IGenericApplicationMessageHandler() = default;

    virtual bool onKeyChar(uint32 character, bool isRepeat) = 0;

    virtual bool onKeyDown(int32 keyCode, uint32 characterCode, bool isRepeat) = 0;
    virtual bool onKeyUp(int32 keyCode, uint32 characterCode, bool isRepeat) = 0;

    virtual bool onMouseDown(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseUp(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseMoved(SharedRef<PlatformWindow> const& platformWindow, Vector2 const& mousePos) = 0;

    virtual void onWindowClose(SharedRef<PlatformWindow> const& platformWindow) = 0;

    virtual void onWindowResized(SharedRef<PlatformWindow> const& platformWindow, uint16 width, uint16 height, bool wasMinimized) = 0;
};

} // namespace px
