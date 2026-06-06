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

bool InputSystem::OnKeyDown([[maybe_unused]] int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, [[maybe_unused]] bool const IsRepeat) {
    EKeyCode const Key{AsEnum<EKeyCode>(KeyCode)};
    KeyEvent const KeyEvent{Key, IsRepeat};

    return ProcessKeyDownEvent(KeyEvent);
}

bool InputSystem::ProcessKeyDownEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessKeyDownEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::OnKeyUp([[maybe_unused]] int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, [[maybe_unused]] bool const IsRepeat) {
    EKeyCode const Key{AsEnum<EKeyCode>(KeyCode)};
    KeyEvent const KeyEvent{Key, IsRepeat};

    return ProcessKeyUpEvent(KeyEvent);
}

bool InputSystem::ProcessKeyUpEvent(KeyEvent const& KeyEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessKeyUpEvent(KeyEvent);
#endif
    return true;
}

bool InputSystem::OnMouseDown([[maybe_unused]] SharedRef<GenericWindow> const& Window, [[maybe_unused]] EMouseButton const Button, [[maybe_unused]] Vector2 const& MousePos) {
    PointerEvent const PointerEvent{Button, MousePos};
    return ProcessMouseButtonDownEvent(PointerEvent);
}

bool InputSystem::ProcessMouseButtonDownEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessMouseButtonDownEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::OnMouseUp([[maybe_unused]] SharedRef<GenericWindow> const& Window, [[maybe_unused]] EMouseButton const Button, [[maybe_unused]] Vector2 const& MousePos) {
    PointerEvent const PointerEvent{Button, MousePos};
    return ProcessMouseButtonUpEvent(PointerEvent);
}

bool InputSystem::ProcessMouseButtonUpEvent(PointerEvent const& MouseEvent) {
#if WITH_IMGUI
    ImGuiInputHandler::ProcessMouseButtonUpEvent(MouseEvent);
#endif
    return true;
}

bool InputSystem::OnMouseMoved(SharedRef<GenericWindow> const& Window, Vector2 const& MousePos) {
    PointerEvent const PointerEvent{EMouseButton::None, MousePos};
    return ProcessMouseMovedEvent(PointerEvent);
}

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
