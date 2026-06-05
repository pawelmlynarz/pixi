// © 2026 Pawel Mlynarz

#include "input/engine_input_system.h"
#include "app/platform_application.h"
#include "window/generic_window.h"

namespace px {

EngineInputSystem::EngineInputSystem(SharedRef<PlatformApplication> OwningApplication)
    : OwningApplication_(std::move(OwningApplication)) {
}

bool EngineInputSystem::OnKeyDown([[maybe_unused]] int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, [[maybe_unused]] bool const IsRepeat) {
    return true;
}

bool EngineInputSystem::OnKeyUp([[maybe_unused]] int32 const KeyCode, [[maybe_unused]] uint32 const CharacterCode, [[maybe_unused]] bool const IsRepeat) {
    return true;
}

bool EngineInputSystem::OnMouseDown([[maybe_unused]] SharedRef<GenericWindow> const& Window, [[maybe_unused]] EMouseButton const Button, [[maybe_unused]] Vector2 const& MousePos) {
    return true;
}

bool EngineInputSystem::OnMouseUp([[maybe_unused]] SharedRef<GenericWindow> const& Window, [[maybe_unused]] EMouseButton const Button, [[maybe_unused]] Vector2 const& MousePos) {
    return true;
}

void EngineInputSystem::OnWindowClose(SharedRef<GenericWindow> const& Window) {
    OwningApplication_->CloseWindow(Window);
}

} // namespace px
