// © 2026 Pawel Mlynarz

#include "input/input_system.h"
#include "app/platform_application.h"
#include "window/generic_window.h"
#include "core_misc.h"

namespace px {

InputSystem::InputSystem(SharedRef<PlatformApplication> const OwningApplication)
    : OwningApplication_(OwningApplication) {
}

bool InputSystem::OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) {
    return true;
}

bool InputSystem::OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) {
    return true;
}

bool InputSystem::OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    return true;
}

bool InputSystem::OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    return true;
}

void InputSystem::OnWindowClose(SharedRef<GenericWindow> const& Window) {
    OwningApplication_->CloseWindow(Window);
}

} // namespace px
