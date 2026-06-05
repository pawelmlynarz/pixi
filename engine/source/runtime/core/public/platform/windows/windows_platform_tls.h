// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "common/types.h"
#include "platform/generic_platform/generic_platform_tls.h"

namespace px {

class WindowsPlatformTLS final : public GenericPlatformTLS {
  public:
    static PXCORE_API uint32 GetCurrentThreadId();
};

using PlatformTLS = WindowsPlatformTLS;

} // namespace px
