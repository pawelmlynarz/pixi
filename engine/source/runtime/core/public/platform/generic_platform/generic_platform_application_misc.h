// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px {

struct GenericPlatformApplicationMisc {
    static PXENGINE_API UniquePtr<class PlatformApplication> createApplication();
};

} // namespace px
