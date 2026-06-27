// © 2026 Pawel Mlynarz

#pragma once

#include "input/generic_message_handler.h"

namespace px {

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    bool onKeyChar(uint32 /*Character*/, bool /*IsRepeat*/) override { return false; };

    bool onKeyDown(int32 const /*KeyCode*/, uint32 const /*CharacterCode*/, bool const /*IsRepeat*/) override { return false; };
    bool onKeyUp(int32 const /*KeyCode*/, uint32 const /*CharacterCode*/, bool const /*IsRepeat*/) override { return false; };

    bool onMouseDown(SharedRef<GenericWindow> const& /*Window*/, EMouseButton const /*Button*/, Vector2 const& /*MousePos*/) override { return false; };
    bool onMouseUp(SharedRef<GenericWindow> const& /*Window*/, EMouseButton const /*Button*/, Vector2 const& /*MousePos*/) override { return false; };
    bool onMouseMoved(SharedRef<GenericWindow> const& /*Window*/, Vector2 const& /*MousePos*/) override { return false; };

    void onWindowClose(SharedRef<GenericWindow> const& window) override {};
    void onWindowResized(SharedRef<GenericWindow> const& window, uint16 width, uint16 height, bool wasMinimized) override {};
};

} // namespace px
