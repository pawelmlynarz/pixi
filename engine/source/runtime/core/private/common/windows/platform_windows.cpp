// � 2026 Pawel Mlynarz

#include "common/platform.h"

namespace px {

uint32 Platform::GetCurrentThreadId() {
    return ::GetCurrentThreadId();
};

} // namespace px
