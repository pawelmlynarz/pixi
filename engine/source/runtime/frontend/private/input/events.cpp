// © 2026 Pawel Mlynarz

#include "input/events.h"

namespace px {

InputEvent::InputEvent(bool bIsRepeat)
    : bIsRepeat_(bIsRepeat) {
}

KeyEvent::KeyEvent(EKeyCode keyCode, bool bIsRepeat)
    : InputEvent(bIsRepeat), keyCode_(keyCode) {
}

CharacterEvent::CharacterEvent(uint32 character, bool bIsRepeat)
    : InputEvent(bIsRepeat), character_(character) {
}

PointerEvent::PointerEvent(EMouseButton mouseButton, Vector2 const& screenPos)
    : InputEvent(false), mouseButton_(mouseButton), screenPos_(screenPos) {
}

} // namespace px
