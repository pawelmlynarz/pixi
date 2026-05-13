// © 2026 Pawel Mlynarz

#include "input/engine_input_system.h"
#include "app/platform_application.h"
#include "window/generic_window.h"
#include "core_misc.h"

namespace px {

EngineInputSystem::EngineInputSystem(SharedRef<PlatformApplication> const OwningApplication)
    : OwningApplication_(OwningApplication) {
}

bool EngineInputSystem::OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) {
    return true;
}

bool EngineInputSystem::OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) {
    return true;
}

bool EngineInputSystem::OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    return true;
}

bool EngineInputSystem::OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton const Button, Vector2 const& MousePos) {
    return true;
}

void EngineInputSystem::OnWindowClose(SharedRef<GenericWindow> const& Window) {
    OwningApplication_->CloseWindow(Window);
}

} // namespace px
