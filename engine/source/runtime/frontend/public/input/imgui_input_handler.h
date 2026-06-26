// © 2026 Pawel Mlynarz

#pragma once

#if WITH_IMGUI

namespace px {

struct CharacterEvent;
struct KeyEvent;
struct PointerEvent;

class ImGuiInputHandler {
  public:
    static bool processCharEvent(CharacterEvent const& charEvent);

    static bool processKeyDownEvent(KeyEvent const& keyEvent);
    static bool processKeyUpEvent(KeyEvent const& keyEvent);

    static bool processMouseButtonDownEvent(PointerEvent const& mouseEvent);
    static bool processMouseButtonUpEvent(PointerEvent const& mouseEvent);
    static bool processMouseMovedEvent(PointerEvent const& mouseEvent);
};

} // namespace px

#endif
