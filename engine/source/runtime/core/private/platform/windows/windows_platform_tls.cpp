// � 2026 Pawel Mlynarz

#include "platform/windows/windows_platform_tls.h"

#include "Windows.h"

namespace px {

uint32 WindowsPlatformTLS::getCurrentThreadId() {
    return ::GetCurrentThreadId();
}

} // namespace px
