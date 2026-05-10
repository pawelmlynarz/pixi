// © 2026 Pawel Mlynarz

#pragma once

#include "app/platform_application.h"
#include "tools/utility.h"

namespace px {

class WindowsApplication final : public PlatformApplication {
  public:
    WindowsApplication() = default;
    ~WindowsApplication() = default;
};

struct WindowsApplicationFactory {
    static PXCORE_API UniquePtr<WindowsApplication> Create();
};

} // namespace px
