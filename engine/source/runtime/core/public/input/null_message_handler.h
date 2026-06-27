// © 2026 Pawel Mlynarz

#pragma once

#include "input/generic_message_handler.h"

namespace px {

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    bool onKeyChar(uint32 /*character*/, bool /*isRepeat*/) override { return false; };

    bool onKeyDown(int32 const /*keyCode*/, uint32 const /*characterCode*/, bool const /*isRepeat*/) override { return false; };
    bool onKeyUp(int32 const /*keyCode*/, uint32 const /*characterCode*/, bool const /*isRepeat*/) override { return false; };

    bool onMouseDown(SharedRef<PlatformWindow> const& /*platformWindow*/, EMouseButton const /*button*/, Vector2 const& /*mousePos*/) override { return false; };
    bool onMouseUp(SharedRef<PlatformWindow> const& /*platformWindow*/, EMouseButton const /*button*/, Vector2 const& /*mousePos*/) override { return false; };
    bool onMouseMoved(SharedRef<PlatformWindow> const& /*platformWindow*/, Vector2 const& /*mousePos*/) override { return false; };

    void onWindowClose(SharedRef<PlatformWindow> const& platformWindow) override {};
    void onWindowResized(SharedRef<PlatformWindow> const& platformWindow, uint16 width, uint16 height, bool wasMinimized) override {};
};

} // namespace px
