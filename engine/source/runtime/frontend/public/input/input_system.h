// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "frontend_module.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

struct KeyEvent;
struct PointerEvent;
class PlatformApplication;

/**
 * System responsible for translating native platform input events to engine input events.
 */
class InputSystem final : NonCopyableNonMovable, public IGenericApplicationMessageHandler {
  public:
    PXFRONTEND_API InputSystem(SharedRef<PlatformApplication> OwningApplication);

    bool OnKeyDown(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) override;
    bool ProcessKeyDownEvent( KeyEvent const& KeyEvent );
    
    bool OnKeyUp(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) override;
    bool ProcessKeyUpEvent( KeyEvent const& KeyEvent );
    
    bool OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) override;
    bool ProcessMouseButtonDownEvent( PointerEvent const& MouseEvent );
    
    bool OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) override;
    bool ProcessMouseButtonUpEvent( PointerEvent const& MouseEvent );
    
    bool OnMouseMoved(SharedRef<GenericWindow> const& Window, Vector2 const& MousePos) override;
    bool ProcessMouseMovedEvent( PointerEvent const& MouseEvent );
    
    void OnWindowClose(SharedRef<GenericWindow> const& Window) override;

  private:
    SharedRef<PlatformApplication> OwningApplication_;
};

} // namespace px
