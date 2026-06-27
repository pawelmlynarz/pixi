// © 2026 Pawel Mlynarz

#pragma once

#include "platform/generic_platform/generic_window_definition.h"
#include "tools/utility.h"
#include "input/generic_message_handler.h"
#include "tools/misc.h"

namespace px {

class PlatformApplication : NonCopyableNonMovable,
                            public EnableSharedFromThis<PlatformApplication> {
  public:
    PlatformApplication();
    virtual ~PlatformApplication() = default;

    virtual void initialize() {}
    virtual void shutdown() {}

    void setMessageHandler(SharedRef<IGenericApplicationMessageHandler> const& inMessageHandler) { messageHandler_ = inMessageHandler; }
    SharedRef<IGenericApplicationMessageHandler> getMessageHandler() { return messageHandler_; }

    virtual UniquePtr<PlatformWindow> createPlatformWindow();
    virtual void initializeWindow(SharedRef<PlatformWindow> const& platformWindow, PlatformWindowDefinition const& windowDefinition) {}
    virtual void closeWindow(SharedRef<PlatformWindow> const& platformWindow) {}

    virtual void pollMessages() {}

  private:
    SharedRef<IGenericApplicationMessageHandler> messageHandler_;
};

} // namespace px
