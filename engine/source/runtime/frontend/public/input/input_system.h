// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
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
    PXENGINE_API InputSystem(SharedPtr<PlatformApplication> const& owningApplication);

    bool onKeyChar(uint32 character, bool isRepeat) override;
    bool processKeyCharEvent(CharacterEvent const& charEvent);

    bool onKeyDown(int32 keyCode, uint32 characterCode, bool isRepeat) override;
    bool processKeyDownEvent(KeyEvent const& keyEvent);

    bool onKeyUp(int32 keyCode, uint32 characterCode, bool isRepeat) override;
    bool processKeyUpEvent(KeyEvent const& keyEvent);

    bool onMouseDown(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) override;
    bool processMouseButtonDownEvent(PointerEvent const& mouseEvent);

    bool onMouseUp(SharedRef<PlatformWindow> const& platformWindow, EMouseButton button, Vector2 const& mousePos) override;
    bool processMouseButtonUpEvent(PointerEvent const& mouseEvent);

    bool onMouseMoved(SharedRef<PlatformWindow> const& platformWindow, Vector2 const& mousePos) override;
    bool processMouseMovedEvent(PointerEvent const& mouseEvent);

    void onWindowClose(SharedRef<PlatformWindow> const& platformWindow) override;
    void onWindowResized(SharedRef<PlatformWindow> const& platformWindow, uint16 width, uint16 height, bool wasMinimized) override;

  private:
    WeakPtr<PlatformApplication> owningApplication_;
};

} // namespace px
