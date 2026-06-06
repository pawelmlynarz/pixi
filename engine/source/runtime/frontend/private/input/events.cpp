// © 2026 Pawel Mlynarz

#include "input/events.h"

namespace px {

InputEvent::InputEvent(bool bIsRepeat)
    : bIsRepeat_(bIsRepeat) {
}

KeyEvent::KeyEvent(EKeyCode KeyCode, bool bIsRepeat)
    : InputEvent(bIsRepeat), KeyCode_(KeyCode) {
}

PointerEvent::PointerEvent(EMouseButton MouseButton, Vector2 const& ScreenPos)
    : InputEvent(false), MouseButton_(MouseButton), ScreenPos_(ScreenPos) {
}

} // namespace px
