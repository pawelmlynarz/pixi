// © 2026 Pawel Mlynarz

#if WITH_IMGUI

#include "input/imgui_input_handler.h"
#include "input/events.h"

#include "imgui.h"

namespace px {

namespace {

constexpr ImGuiKey RemapKey(EKeyCode const KeyCode) {
    switch (KeyCode) {
    case EKeyCode::A: return ImGuiKey_A;
    case EKeyCode::B: return ImGuiKey_B;
    case EKeyCode::C: return ImGuiKey_C;
    case EKeyCode::D: return ImGuiKey_D;
    case EKeyCode::E: return ImGuiKey_E;
    case EKeyCode::F: return ImGuiKey_F;
    case EKeyCode::G: return ImGuiKey_G;
    case EKeyCode::H: return ImGuiKey_H;
    case EKeyCode::I: return ImGuiKey_I;
    case EKeyCode::J: return ImGuiKey_J;
    case EKeyCode::K: return ImGuiKey_K;
    case EKeyCode::L: return ImGuiKey_L;
    case EKeyCode::M: return ImGuiKey_M;
    case EKeyCode::N: return ImGuiKey_N;
    case EKeyCode::O: return ImGuiKey_O;
    case EKeyCode::P: return ImGuiKey_P;
    case EKeyCode::Q: return ImGuiKey_Q;
    case EKeyCode::R: return ImGuiKey_R;
    case EKeyCode::S: return ImGuiKey_S;
    case EKeyCode::T: return ImGuiKey_T;
    case EKeyCode::U: return ImGuiKey_U;
    case EKeyCode::V: return ImGuiKey_V;
    case EKeyCode::W: return ImGuiKey_W;
    case EKeyCode::X: return ImGuiKey_X;
    case EKeyCode::Y: return ImGuiKey_Y;
    case EKeyCode::Z: return ImGuiKey_Z;

    case EKeyCode::Num0: return ImGuiKey_0;
    case EKeyCode::Num1: return ImGuiKey_1;
    case EKeyCode::Num2: return ImGuiKey_2;
    case EKeyCode::Num3: return ImGuiKey_3;
    case EKeyCode::Num4: return ImGuiKey_4;
    case EKeyCode::Num5: return ImGuiKey_5;
    case EKeyCode::Num6: return ImGuiKey_6;
    case EKeyCode::Num7: return ImGuiKey_7;
    case EKeyCode::Num8: return ImGuiKey_8;
    case EKeyCode::Num9: return ImGuiKey_9;

    case EKeyCode::Space: return ImGuiKey_Space;
    case EKeyCode::Apostrophe: return ImGuiKey_Apostrophe;
    case EKeyCode::Comma: return ImGuiKey_Comma;
    case EKeyCode::Minus: return ImGuiKey_Minus;
    case EKeyCode::Period: return ImGuiKey_Period;
    case EKeyCode::Slash: return ImGuiKey_Slash;
    case EKeyCode::Semicolon: return ImGuiKey_Semicolon;
    case EKeyCode::Equal: return ImGuiKey_Equal;
    case EKeyCode::LeftBracket: return ImGuiKey_LeftBracket;
    case EKeyCode::Backslash: return ImGuiKey_Backslash;
    case EKeyCode::RightBracket: return ImGuiKey_RightBracket;
    case EKeyCode::GraveAccent: return ImGuiKey_GraveAccent;

    case EKeyCode::Escape: return ImGuiKey_Escape;
    case EKeyCode::Enter: return ImGuiKey_Enter;
    case EKeyCode::Tab: return ImGuiKey_Tab;
    case EKeyCode::Backspace: return ImGuiKey_Backspace;
    case EKeyCode::Insert: return ImGuiKey_Insert;
    case EKeyCode::Delete: return ImGuiKey_Delete;

    case EKeyCode::Right: return ImGuiKey_RightArrow;
    case EKeyCode::Left: return ImGuiKey_LeftArrow;
    case EKeyCode::Down: return ImGuiKey_DownArrow;
    case EKeyCode::Up: return ImGuiKey_UpArrow;

    case EKeyCode::PageUp: return ImGuiKey_PageUp;
    case EKeyCode::PageDown: return ImGuiKey_PageDown;
    case EKeyCode::Home: return ImGuiKey_Home;
    case EKeyCode::End: return ImGuiKey_End;

    case EKeyCode::CapsLock: return ImGuiKey_CapsLock;
    case EKeyCode::ScrollLock: return ImGuiKey_ScrollLock;
    case EKeyCode::NumLock: return ImGuiKey_NumLock;
    case EKeyCode::PrintScreen: return ImGuiKey_PrintScreen;
    case EKeyCode::Pause: return ImGuiKey_Pause;

    case EKeyCode::F1: return ImGuiKey_F1;
    case EKeyCode::F2: return ImGuiKey_F2;
    case EKeyCode::F3: return ImGuiKey_F3;
    case EKeyCode::F4: return ImGuiKey_F4;
    case EKeyCode::F5: return ImGuiKey_F5;
    case EKeyCode::F6: return ImGuiKey_F6;
    case EKeyCode::F7: return ImGuiKey_F7;
    case EKeyCode::F8: return ImGuiKey_F8;
    case EKeyCode::F9: return ImGuiKey_F9;
    case EKeyCode::F10: return ImGuiKey_F10;
    case EKeyCode::F11: return ImGuiKey_F11;
    case EKeyCode::F12: return ImGuiKey_F12;

    case EKeyCode::LeftShift: return ImGuiKey_LeftShift;
    case EKeyCode::LeftCtrl: return ImGuiKey_LeftCtrl;
    case EKeyCode::LeftAlt: return ImGuiKey_LeftAlt;
    case EKeyCode::LeftSuper: return ImGuiKey_LeftSuper;

    case EKeyCode::RightShift: return ImGuiKey_RightShift;
    case EKeyCode::RightCtrl: return ImGuiKey_RightCtrl;
    case EKeyCode::RightAlt: return ImGuiKey_RightAlt;
    case EKeyCode::RightSuper: return ImGuiKey_RightSuper;
    case EKeyCode::None:
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

bool ImGuiInputHandler::ProcessCharEvent(CharacterEvent const& CharEvent) {
    ImGuiIO& IO{ImGui::GetIO()};
    IO.AddInputCharacter(CharEvent.GetCharacter());

    return true;
}

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
