// © 2026 Pawel Mlynarz

#pragma once

#include "common/windows/types_windows.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

class PlatformApplication;

class InputSystem final : NonCopyableNonMovable, public IGenericApplicationMessageHandler {
public:
    InputSystem(SharedRef<PlatformApplication> const OwningApplication);
    
    virtual bool OnKeyDown(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override;
    virtual bool OnKeyUp(int32 const KeyCode, uint32 const CharacterCode, bool const IsRepeat) override;

    virtual bool OnMouseDown(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) override;
    virtual bool OnMouseUp(SharedPtr<GenericWindow> const& Window, EMouseButton const Button) override;

    virtual void OnWindowClose(SharedRef<GenericWindow> const& Window) override;
    
private:
    SharedRef<PlatformApplication> OwningApplication_;
};

} // namespace px
