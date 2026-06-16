// © 2026 Pawel Mlynarz

#pragma once

// pxcore
#include "common/types.h"
#include "input/key_codes.h"

namespace px {

/**
 * Base class for all mouse and key events.
 */
struct InputEvent {
    explicit InputEvent(bool bIsRepeat);

    bool IsRepeat() const { return bIsRepeat_; }

  private:
    bool bIsRepeat_{false};
};

/**
 * KeyEvent describes a key action (keyboard/controller key/button pressed or released).
 */
struct KeyEvent : public InputEvent {
    KeyEvent(EKeyCode KeyCode, bool bIsRepeat);

    EKeyCode GetKeyCode() const { return KeyCode_; }

  private:
    EKeyCode KeyCode_{EKeyCode::None};
};

/**
 * CharacterEvent describes a keyboard action where the utf-16 code is given (keyboard/controller key/button pressed or released).
 */
struct CharacterEvent : public InputEvent {
    CharacterEvent(uint32 Character, bool bIsRepeat);

    uint32 GetCharacter() const { return Character_; }

  private:
    uint32 Character_{0};
};

/**
 * PointerEvent describes a pointer action (mouse).
 */
struct PointerEvent : public InputEvent {
    PointerEvent(EMouseButton MouseButton, Vector2 const& ScreenPos);

    EMouseButton GetButton() const { return MouseButton_; }
    Vector2 GetScreenPos() const { return ScreenPos_; }

  private:
    EMouseButton MouseButton_{EMouseButton::None};
    Vector2 ScreenPos_;
};

} // namespace px
