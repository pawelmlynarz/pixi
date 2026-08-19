// © 2026 Pawel Mlynarz

#pragma once

#include "input/generic_message_handler.h"

namespace px {

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    bool onKeyChar(u32 /*character*/, bool /*isRepeat*/) override { return false; };

    bool onKeyDown(i32 const /*keyCode*/, u32 const /*characterCode*/, bool const /*isRepeat*/) override { return false; };
    bool onKeyUp(i32 const /*keyCode*/, u32 const /*characterCode*/, bool const /*isRepeat*/) override { return false; };

    bool onMouseDown(SharedRef<PlatformWindow> const& /*platformWindow*/, EMouseButton const /*button*/, Vector2 const& /*mousePos*/) override { return false; };
    bool onMouseUp(SharedRef<PlatformWindow> const& /*platformWindow*/, EMouseButton const /*button*/, Vector2 const& /*mousePos*/) override { return false; };
    bool onMouseMoved(SharedRef<PlatformWindow> const& /*platformWindow*/, Vector2 const& /*mousePos*/) override { return false; };

    void onWindowClose(SharedRef<PlatformWindow> const& platformWindow) override {};
    void onWindowResized(SharedRef<PlatformWindow> const& platformWindow, u16 width, u16 height, bool wasMinimized) override {};
};

} // namespace px
