// © 2026 Pawel Mlynarz

#pragma once

namespace px {

struct GenericPlatformProperties {
    static char const* platformName();

    static constexpr bool supportsWindowedMode() {
        return false;
    }
};

} // namespace px
