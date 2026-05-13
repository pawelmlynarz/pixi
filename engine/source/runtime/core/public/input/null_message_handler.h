// © 2026 Pawel Mlynarz

#pragma once

#include "input/generic_message_handler.h"

namespace px {

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    virtual bool OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override { return false; };
    virtual bool OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override { return false; };

    virtual bool OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) override { return false; };
    virtual bool OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) override { return false; };

    virtual void OnWindowClose(SharedRef<GenericWindow> const& Window) override {};
};

} // namespace px
