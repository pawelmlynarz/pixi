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

    virtual bool OnKeyDown(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) = 0;
    virtual bool OnKeyUp(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) = 0;

    virtual bool OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) = 0;
    virtual bool OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) = 0;
    virtual bool OnMouseMoved(SharedRef<GenericWindow> const& Window, Vector2 const& MousePos) = 0;

    virtual void OnWindowClose(SharedRef<GenericWindow> const& Window) = 0;
};

} // namespace px
