// © 2026 Pawel Mlynarz

#include "input/input_system.h"
#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "input/events.h"

#if WITH_IMGUI
#include "input/imgui_input_handler.h"
#endif

namespace px {

InputSystem::InputSystem(SharedRef<PlatformApplication> owningApplication)
    : owningApplication_(std::move(owningApplication)) {
}

bool InputSystem::onKeyChar(uint32 character, bool isRepeat) {
    CharacterEvent const charEvent{character, isRepeat};

    return processKeyCharEvent(charEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processKeyCharEvent(CharacterEvent const& CharEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processCharEvent(CharEvent);
#endif
    return true;
}

bool InputSystem::onKeyDown(int32 const keyCode, [[maybe_unused]] uint32 const characterCode, bool const isRepeat) {
    EKeyCode const key{asEnum<EKeyCode>(keyCode)};
    KeyEvent const keyEvent{key, isRepeat};

    return processKeyDownEvent(keyEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processKeyDownEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processKeyDownEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::onKeyUp(int32 const keyCode, [[maybe_unused]] uint32 const characterCode, bool const isRepeat) {
    EKeyCode const key{asEnum<EKeyCode>(keyCode)};
    KeyEvent const keyEvent{key, isRepeat};

    return processKeyUpEvent(keyEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processKeyUpEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processKeyUpEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::onMouseDown([[maybe_unused]] SharedRef<GenericWindow> const& window, EMouseButton const button, Vector2 const& mousePos) {
    PointerEvent const pointerEvent{button, mousePos};
    return processMouseButtonDownEvent(pointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processMouseButtonDownEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processMouseButtonDownEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::onMouseUp([[maybe_unused]] SharedRef<GenericWindow> const& window, EMouseButton const button, Vector2 const& mousePos) {
    PointerEvent const pointerEvent{button, mousePos};
    return processMouseButtonUpEvent(pointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processMouseButtonUpEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processMouseButtonUpEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::onMouseMoved([[maybe_unused]] SharedRef<GenericWindow> const& window, Vector2 const& mousePos) {
    PointerEvent const pointerEvent{EMouseButton::None, mousePos};
    return processMouseMovedEvent(pointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::processMouseMovedEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::processMouseMovedEvent(MouseEvent);
#endif
    return true;
}

void InputSystem::onWindowClose(SharedRef<GenericWindow> const& window) {
    owningApplication_->closeWindow(window);
}

} // namespace px
