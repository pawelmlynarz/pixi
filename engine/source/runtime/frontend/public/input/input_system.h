// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "frontend_module.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

struct CharacterEvent;
struct KeyEvent;
struct PointerEvent;
class PlatformApplication;

/**
 * System responsible for translating native platform input events to engine input events.
 */
class InputSystem final : NonCopyableNonMovable, public IGenericApplicationMessageHandler {
  public:
    PXFRONTEND_API InputSystem(SharedRef<PlatformApplication> owningApplication);

    bool onKeyChar(uint32 character, bool isRepeat) override;
    bool processKeyCharEvent(CharacterEvent const& charEvent);

    bool onKeyDown(int32 keyCode, uint32 characterCode, bool isRepeat) override;
    bool processKeyDownEvent(KeyEvent const& keyEvent);

    bool onKeyUp(int32 keyCode, uint32 characterCode, bool isRepeat) override;
    bool processKeyUpEvent(KeyEvent const& keyEvent);

    bool onMouseDown(SharedRef<GenericWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) override;
    bool processMouseButtonDownEvent(PointerEvent const& mouseEvent);

    bool onMouseUp(SharedRef<GenericWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) override;
    bool processMouseButtonUpEvent(PointerEvent const& mouseEvent);

    bool onMouseMoved(SharedRef<GenericWindow> const& platformWindow, Vector2 const& mousePos) override;
    bool processMouseMovedEvent(PointerEvent const& mouseEvent);

    void onWindowClose(SharedRef<GenericWindow> const& platformWindow) override;
    void onWindowResized(SharedRef<GenericWindow> const& platformWindow, uint16 width, uint16 height, bool wasMinimized) override;

  private:
    SharedRef<PlatformApplication> owningApplication_;
};

} // namespace px
