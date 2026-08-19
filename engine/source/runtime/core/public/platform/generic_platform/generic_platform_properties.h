// © 2026 Pawel Mlynarz

#pragma once

namespace px {

struct GenericPlatformProperties {
    static cstring platformName();

    static constexpr bool supportsWindowedMode() {
        return false;
    }
};

} // namespace px
