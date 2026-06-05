// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

class PlatformApplication;

class EngineInputSystem final : NonCopyableNonMovable, public IGenericApplicationMessageHandler {
  public:
    PXCORE_API EngineInputSystem(SharedRef<PlatformApplication> OwningApplication);

    bool OnKeyDown(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) override;
    bool OnKeyUp(int32 KeyCode, uint32 CharacterCode, bool IsRepeat) override;

    bool OnMouseDown(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) override;
    bool OnMouseUp(SharedRef<GenericWindow> const& Window, EMouseButton Button, Vector2 const& MousePos) override;

    void OnWindowClose(SharedRef<GenericWindow> const& Window) override;

  private:
    SharedRef<PlatformApplication> OwningApplication_;
};

} // namespace px
