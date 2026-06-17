// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

#include <string_view>

// NOLINTBEGIN

#define PX_VERSION_MAJOR 0
#define PX_VERSION_MINOR 0
#define PX_VERSION_PATCH 0

#define PX_VERSION_STRING          \
    PX_STRINGIZE(PX_VERSION_MAJOR) \
    "." PX_STRINGIZE(PX_VERSION_MINOR) "." PX_STRINGIZE(PX_VERSION_PATCH)

namespace px {

constexpr std::string_view VersionString() {
    return PX_VERSION_STRING;
}

} // namespace px

// NOLINTEND
