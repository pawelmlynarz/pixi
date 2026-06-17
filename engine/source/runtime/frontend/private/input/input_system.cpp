// © 2026 Pawel Mlynarz

#include "input/input_system.h"
#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "input/events.h"

#if WITH_IMGUI
#include "input/imgui_input_handler.h"
#endif

namespace px {

InputSystem::InputSystem(SharedRef<PlatformApplication> OwningApplication)
    : OwningApplication_(std::move(OwningApplication)) {
}

bool InputSystem::OnKeyChar(uint32 Character, bool IsRepeat) {
    CharacterEvent const CharEvent{Character, IsRepeat};

    return ProcessKeyCharEvent(CharEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessKeyCharEvent(CharacterEvent const& CharEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessCharEvent(CharEvent);
#endif
    return true;
}

bool InputSystem::OnKeyDown(int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, bool const IsRepeat) {
    EKeyCode const Key{AsEnum<EKeyCode>(KeyCode)};
    KeyEvent const KeyEvent{Key, IsRepeat};

    return ProcessKeyDownEvent(KeyEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessKeyDownEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessKeyDownEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::OnKeyUp(int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, bool const IsRepeat) {
    EKeyCode const Key{AsEnum<EKeyCode>(KeyCode)};
    KeyEvent const KeyEvent{Key, IsRepeat};

    return ProcessKeyUpEvent(KeyEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessKeyUpEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessKeyUpEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::OnMouseDown([[maybe_unused]] SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    PointerEvent const PointerEvent{Button, MousePos};
    return ProcessMouseButtonDownEvent(PointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessMouseButtonDownEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessMouseButtonDownEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::OnMouseUp([[maybe_unused]] SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    PointerEvent const PointerEvent{Button, MousePos};
    return ProcessMouseButtonUpEvent(PointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessMouseButtonUpEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessMouseButtonUpEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::OnMouseMoved([[maybe_unused]] SharedRef<GenericWindow> const& Window, Vector2 const& MousePos) {
    PointerEvent const PointerEvent{EMouseButton::None, MousePos};
    return ProcessMouseMovedEvent(PointerEvent);
}

// NOLINTNEXTLINE(*)
bool InputSystem::ProcessMouseMovedEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessMouseMovedEvent(MouseEvent);
#endif
    return true;
}

void InputSystem::OnWindowClose(SharedRef<GenericWindow> const& Window) {
    OwningApplication_->CloseWindow(Window);
}

} // namespace px
