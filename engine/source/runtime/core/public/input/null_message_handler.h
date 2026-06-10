// © 2026 Pawel Mlynarz

#pragma once

#include "input/generic_message_handler.h"

namespace px {

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    bool OnKeyDown(int32 const /*KeyCode*/, uint32 const /*CharacterCode*/, bool const /*IsRepeat*/) override { return false; };
    bool OnKeyUp(int32 const /*KeyCode*/, uint32 const /*CharacterCode*/, bool const /*IsRepeat*/) override { return false; };

    bool OnMouseDown(SharedRef<GenericWindow> const& /*Window*/, EMouseButton const /*Button*/, Vector2 const& /*MousePos*/) override { return false; };
    bool OnMouseUp(SharedRef<GenericWindow> const& /*Window*/, EMouseButton const /*Button*/, Vector2 const& /*MousePos*/) override { return false; };
    bool OnMouseMoved(SharedRef<GenericWindow> const& /*Window*/, Vector2 const& /*MousePos*/) override { return false; };

    void OnWindowClose(SharedRef<GenericWindow> const& Window) override {};
};

} // namespace px
