// © 2026 Pawel Mlynarz

#include "memory/sys_alloc.h"

#ifdef _MSC_VER
#include <malloc.h>
#endif

namespace px {

void* sysAlignedAllocate(size_t const size, size_t const alignment) noexcept {
#ifdef _MSC_VER
    return _aligned_malloc(size, alignment);
#else
#error Compiler not supported.
#endif
}

void sysAlignedFree(void* const ptr) noexcept {
#ifdef _MSC_VER
    _aligned_free(ptr);
#else
#error Compiler not supported.
#endif
}

} // namespace px
