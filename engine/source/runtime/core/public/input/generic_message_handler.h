// © 2026 Pawel Mlynarz

#pragma once

#include "tools/utility.h"

namespace px {

enum class EMouseButton : uint8 {
    Left,
    Middle,
    Right
};

class GenericWindow;

class IGenericApplicationMessageHandler {
  public:
    virtual ~IGenericApplicationMessageHandler() = default;

    virtual bool OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) = 0;
    virtual bool OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) = 0;

    virtual bool OnMouseDown(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) = 0;
    virtual bool OnMouseUp(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) = 0;

    virtual void OnWindowClose(SharedRef<GenericWindow> const& Window) = 0;
};

class NullApplicationMessageHandler final : public IGenericApplicationMessageHandler {
  public:
    virtual bool OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override { return false; };
    virtual bool OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override { return false; };

    virtual bool OnMouseDown(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) override { return false; };
    virtual bool OnMouseUp(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) override { return false; };

    virtual void OnWindowClose(SharedRef<GenericWindow> const& Window) override {};
};

} // namespace px
