// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "input/null_message_handler.h"

namespace px {

PlatformApplication::PlatformApplication()
    : MessageHandler_(MakeShared<NullApplicationMessageHandler>()) {
}

UniquePtr<GenericWindow> PlatformApplication::CreatePlatformWindow() {
    return MakeUnique<GenericWindow>();
}

} // namespace px
