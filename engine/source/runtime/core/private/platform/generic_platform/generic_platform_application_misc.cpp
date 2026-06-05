// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_platform_application_misc.h"
#include "platform/generic_platform/generic_application.h"

namespace px {

UniquePtr<PlatformApplication> GenericPlatformApplicationMisc::CreateApplication() {
    return MakeUnique<PlatformApplication>();
}

} // namespace px
