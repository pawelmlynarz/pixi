// © 2026 Pawel Mlynarz

#if WITH_IMGUI

#include "input/imgui_input_handler.h"
#include "input/events.h"

#include "imgui.h"

namespace px {

namespace {

ImGuiKey RemapKey(EKeyCode const KeyCode) {
    switch (KeyCode) {
    case EKeyCode::A:
        return ImGuiKey_A;
    case EKeyCode::B:
        return ImGuiKey_B;
    case EKeyCode::C:
        return ImGuiKey_C;
    case EKeyCode::D:
        return ImGuiKey_D;
    case EKeyCode::E:
        return ImGuiKey_E;
    case EKeyCode::F:
        return ImGuiKey_F;
    case EKeyCode::G:
        return ImGuiKey_G;
    default:
        EnsureNoEntry("Key not mapped.");
        return ImGuiKey_None;
    }
}

int32 RemapMouseButton(EMouseButton const MouseButton) {
    if (MouseButton == EMouseButton::Left) {
        return 0;
    }
    if (MouseButton == EMouseButton::Middle) {
        return 2;
    }
    if (MouseButton == EMouseButton::Right) {
        return 1;
    }
    EnsureNoEntry("Mouse button not mapped.");
    return 0;
}

} // namespace

bool ImGuiInputHandler::ProcessKeyDownEvent(KeyEvent const& KeyEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    ImGuiKey const RemappedKey{RemapKey(KeyEvent.GetKeyCode())};
    IO.AddKeyEvent(RemappedKey, true);

    return true;
}

bool ImGuiInputHandler::ProcessKeyUpEvent(KeyEvent const& KeyEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    ImGuiKey const RemappedKey{RemapKey(KeyEvent.GetKeyCode())};
    IO.AddKeyEvent(RemappedKey, false);

    return true;
}

bool ImGuiInputHandler::ProcessMouseButtonDownEvent(PointerEvent const& MouseEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    int32 const RemappedButton{RemapMouseButton(MouseEvent.GetButton())};
    IO.AddMouseButtonEvent(RemappedButton, true);

    return true;
}

bool ImGuiInputHandler::ProcessMouseButtonUpEvent(PointerEvent const& MouseEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    int32 const RemappedButton{RemapMouseButton(MouseEvent.GetButton())};
    IO.AddMouseButtonEvent(RemappedButton, false);

    return true;
}

bool ImGuiInputHandler::ProcessMouseMovedEvent(PointerEvent const& MouseEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    Vector2 const Pos{MouseEvent.GetScreenPos()};
    IO.AddMousePosEvent(Pos.x, Pos.y);

    return true;
}

} // namespace px

#endif
