// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/utility.h"

namespace px {

struct GenericPlatformApplicationMisc {
    static PXCORE_API UniquePtr<class PlatformApplication> CreateApplication();
};

} // namespace px

#include COMPILED_PLATFORM_HEADER(application_misc.h)
