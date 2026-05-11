// © 2026 Pawel Mlynarz

#include "app/platform_application.h"
#include "window/generic_window.h"

namespace px {

PlatformApplication::PlatformApplication() 
    : MessageHandler_(MakeShared<NullApplicationMessageHandler>()) {
}

UniquePtr<GenericWindow> PlatformApplication::CreatePlatformWindow() {
    return MakeUnique<GenericWindow>();
}

} // namespace px
