// © 2026 Pawel Mlynarz

#pragma once

#if WITH_IMGUI

namespace px {

struct CharacterEvent;
struct KeyEvent;
struct PointerEvent;

class ImGuiInputHandler {
  public:
    static bool ProcessCharEvent(CharacterEvent const& CharEvent);

    static bool ProcessKeyDownEvent(KeyEvent const& KeyEvent);
    static bool ProcessKeyUpEvent(KeyEvent const& KeyEvent);

    static bool ProcessMouseButtonDownEvent(PointerEvent const& MouseEvent);
    static bool ProcessMouseButtonUpEvent(PointerEvent const& MouseEvent);
    static bool ProcessMouseMovedEvent(PointerEvent const& MouseEvent);
};

} // namespace px

#endif
