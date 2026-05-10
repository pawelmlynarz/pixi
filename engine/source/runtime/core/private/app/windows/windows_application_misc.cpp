// © 2026 Pawel Mlynarz

#include "app/windows/windows_application_misc.h"
#include "app/windows/windows_application.h"

namespace px {

UniquePtr<PlatformApplication> WindowsApplicationMisc::CreateApplication() {
    return WindowsApplicationFactory::Create();
}

} // namespace px
