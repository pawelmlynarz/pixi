// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "input/null_message_handler.h"

namespace px {

PlatformApplication::PlatformApplication()
    : messageHandler_(makeShared<NullApplicationMessageHandler>()) {
}

UniquePtr<GenericWindow> PlatformApplication::createPlatformWindow() {
    return makeUnique<GenericWindow>();
}

} // namespace px
