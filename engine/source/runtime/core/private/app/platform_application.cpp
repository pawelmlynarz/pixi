// © 2026 Pawel Mlynarz

#include "app/platform_application.h"
#include "window/generic_window.h"

namespace px {

UniquePtr<GenericWindow> PlatformApplication::CreatePlatformWindow() {
    return MakeUnique<GenericWindow>();
}

} // namespace px
