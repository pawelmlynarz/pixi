// © 2026 Pawel Mlynarz

#include "app/platform_application_misc.h"
#include "app/platform_application.h"

namespace px {

UniquePtr<PlatformApplication> GenericPlatformApplicationMisc::CreateApplication() {
    return MakeUnique<PlatformApplication>();
}

} // namespace px
