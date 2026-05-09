// � 2026 Pawel Mlynarz

#include "common/platform.h"

uint32 Platform::GetCurrentThreadId() {
    return ::GetCurrentThreadId();
};
