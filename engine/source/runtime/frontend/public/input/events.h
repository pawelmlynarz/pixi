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

    bool isRepeat() const { return bIsRepeat_; }

  private:
    bool bIsRepeat_{false};
};

/**
 * KeyEvent describes a key action (keyboard/controller key/button pressed or released).
 */
struct KeyEvent : public InputEvent {
    KeyEvent(EKeyCode keyCode, bool bIsRepeat);

    EKeyCode getKeyCode() const { return keyCode_; }

  private:
    EKeyCode keyCode_{EKeyCode::None};
};

/**
 * CharacterEvent describes a keyboard action where the utf-16 code is given (keyboard/controller key/button pressed or released).
 */
struct CharacterEvent : public InputEvent {
    CharacterEvent(uint32 character, bool bIsRepeat);

    uint32 getCharacter() const { return character_; }

  private:
    uint32 character_{0};
};

/**
 * PointerEvent describes a pointer action (mouse).
 */
struct PointerEvent : public InputEvent {
    PointerEvent(EMouseButton mouseButton, Vector2 const& screenPos);

    EMouseButton getButton() const { return mouseButton_; }
    Vector2 getScreenPos() const { return screenPos_; }

  private:
    EMouseButton mouseButton_{EMouseButton::None};
    Vector2 screenPos_;
};

} // namespace px
