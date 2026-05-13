// © 2026 Pawel Mlynarz

#include "app/platform_application.h"
#include "input/null_message_handler.h"
#include "window/generic_window.h"

namespace px {

PlatformApplication::PlatformApplication()
    : MessageHandler_(MakeShared<NullApplicationMessageHandler>()) {
}

UniquePtr<GenericWindow> PlatformApplication::CreatePlatformWindow() {
    return MakeUnique<GenericWindow>();
}

} // namespace px
