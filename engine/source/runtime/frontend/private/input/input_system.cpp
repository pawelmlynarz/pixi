// © 2026 Pawel Mlynarz

#include "input/input_system.h"
#include "app/pixi_application.h"
#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "input/events.h"
#include "rendering/renderer.h"

#if WITH_IMGUI
#include "input/imgui_input_handler.h"
#endif

namespace px {

InputSystem::InputSystem(SharedPtr<PlatformApplication> const& owningApplication)
    : owningApplication_(owningApplication) {
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

bool InputSystem::onMouseDown([[maybe_unused]] SharedRef<PlatformWindow> const& platformWindow, EMouseButton const button, Vector2 const& mousePos) {
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

bool InputSystem::onMouseUp([[maybe_unused]] SharedRef<PlatformWindow> const& platformWindow, EMouseButton const button, Vector2 const& mousePos) {
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

bool InputSystem::onMouseMoved([[maybe_unused]] SharedRef<PlatformWindow> const& platformWindow, Vector2 const& mousePos) {
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

void InputSystem::onWindowClose(SharedRef<PlatformWindow> const& platformWindow) {
    owningApplication_.lock()->closeWindow(platformWindow);
}

void InputSystem::onWindowResized(SharedRef<PlatformWindow> const& platformWindow, uint16 width, uint16 height, [[maybe_unused]] bool wasMinimized) {
    Renderer& renderer{dynamic_cast<Renderer&>(SimpleApplication::get().getRenderer())};

    // Flush the rendering command queue to ensure that there aren't pending viewport draw commands for the old viewport size.
    renderer.flushCommands();

    if (SharedPtr const window{SimpleApplication::get().findWindowByPlatformWindow(platformWindow)}) {
        renderer.requestResizeViewport(window, width, height);
    }
}

} // namespace px
