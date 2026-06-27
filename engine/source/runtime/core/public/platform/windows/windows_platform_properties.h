// © 2026 Pawel Mlynarz

#pragma once

#include "platform/generic_platform/generic_platform_properties.h"

namespace px {

struct WindowsPlatformProperties final : GenericPlatformProperties {
    static constexpr char const* platformName() {
        return "Windows";
    }

    static constexpr bool supportsWindowedMode() {
        return true;
    }
};

using PlatformProperties = WindowsPlatformProperties;

} // namespace px
