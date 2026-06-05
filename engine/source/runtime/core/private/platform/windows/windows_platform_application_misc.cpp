// © 2026 Pawel Mlynarz

#include "platform/windows/windows_platform_application_misc.h"
#include "platform/windows/windows_application.h"

namespace px {

UniquePtr<PlatformApplication> WindowsApplicationMisc::CreateApplication() {
    return WindowsApplicationFactory::Create();
}

} // namespace px
