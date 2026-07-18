// © 2026 Pawel Mlynarz

#include "memory/mallocator.h"
#include "common/types.h"

namespace px {

class Mallocator final : public Allocator {
  public:
    void* alloc(size_t size) override;
    void free(void* addr) override;
    void* allocAligned(size_t size, size_t align) override;
    void* realloc(void* addr, size_t size, bool preserve = true) override;
};

void* Mallocator::alloc(size_t const size) {
    return _aligned_malloc(size, alignof(std::max_align_t));
}

void Mallocator::free(void* const addr) {
    _aligned_free(addr);
}

void* Mallocator::allocAligned(size_t const size, size_t const align) {
    pxAssert(isPowerOfTwo(align));

    return _aligned_malloc(size, std::max(align, sDefaultAlign));
}

void* Mallocator::realloc(void* const addr, size_t const size, bool /*preserve*/) {
    return _aligned_realloc(addr, size, alignof(std::max_align_t));
}

template <>
Allocator& getDefaultInstance<Mallocator>() {
    static Mallocator defaultInstance;
    return defaultInstance;
}

} // namespace px
