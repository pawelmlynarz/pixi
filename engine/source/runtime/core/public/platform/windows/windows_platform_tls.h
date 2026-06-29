// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "platform/generic_platform/generic_platform_tls.h"

namespace px {

class WindowsPlatformTLS final : public GenericPlatformTLS {
  public:
    static PXENGINE_API uint32 getCurrentThreadId();
};

using PlatformTLS = WindowsPlatformTLS;

} // namespace px
