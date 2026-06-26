// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/utility.h"

namespace px {

struct GenericPlatformApplicationMisc {
    static PXCORE_API UniquePtr<class PlatformApplication> createApplication();
};

} // namespace px
