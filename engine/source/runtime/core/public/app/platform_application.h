// © 2026 Pawel Mlynarz

#pragma once

#include "tools/utility.h"
#include "window/generic_window_definition.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

class PlatformApplication : NonCopyableNonMovable,
                            public EnableSharedFromThis<PlatformApplication> {
  public:
    PlatformApplication();
    virtual ~PlatformApplication() = default;

    virtual void Initialize() {}
    virtual void Shutdown() {}

    void SetMessageHandler(SharedRef<IGenericApplicationMessageHandler> const& InMessageHandler) { MessageHandler_ = InMessageHandler; }
    SharedRef<IGenericApplicationMessageHandler> GetMessageHandler() { return MessageHandler_; }

    virtual UniquePtr<GenericWindow> CreatePlatformWindow();
    virtual void InitializeWindow(SharedRef<GenericWindow> const&, GenericWindowDefinition const&) {}
    virtual void CloseWindow(SharedRef<GenericWindow> const& Window) {}

    virtual void PollMessages() {}

  private:
    SharedRef<IGenericApplicationMessageHandler> MessageHandler_;
};

} // namespace px
