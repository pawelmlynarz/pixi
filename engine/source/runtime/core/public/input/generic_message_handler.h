// © 2026 Pawel Mlynarz

#pragma once

#include "input/key_codes.h"
#include "tools/utility.h"
#include "common/types.h"

namespace px {

class GenericWindow;

class IGenericApplicationMessageHandler {
  public:
    virtual ~IGenericApplicationMessageHandler() = default;

    virtual bool onKeyChar(uint32 character, bool isRepeat) = 0;

    virtual bool onKeyDown(int32 keyCode, uint32 characterCode, bool isRepeat) = 0;
    virtual bool onKeyUp(int32 keyCode, uint32 characterCode, bool isRepeat) = 0;

    virtual bool onMouseDown(SharedRef<GenericWindow> const& window, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseUp(SharedRef<GenericWindow> const& window, EMouseButton button, Vector2 const& mousePos) = 0;
    virtual bool onMouseMoved(SharedRef<GenericWindow> const& window, Vector2 const& mousePos) = 0;

    virtual void onWindowClose(SharedRef<GenericWindow> const& window) = 0;

    virtual void onWindowResized(SharedRef<GenericWindow> const& window, uint16 width, uint16 height, bool wasMinimized) = 0;
};

} // namespace px
