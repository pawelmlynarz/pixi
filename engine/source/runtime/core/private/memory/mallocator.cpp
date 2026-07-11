// © 2026 Pawel Mlynarz

#include "memory/mallocator.h"

namespace px {

class Mallocator final : public Allocator {
  public:
    void* alloc(size_t size) override;
    void free(void* addr) override;
    void* allocAligned(size_t size, size_t align) override;
    void* realloc(void* addr, size_t size, bool preserve = true) override;
};

void* Mallocator::alloc(size_t const size) {
    return ::malloc(size);
}

void Mallocator::free(void* const addr) {
    ::free(addr);
}

void* Mallocator::allocAligned(size_t const size, size_t const align) {
    return ::_aligned_malloc(size, align);
}

void* Mallocator::realloc(void* const addr, size_t const size, bool /*preserve*/) {
    return ::realloc(addr, size);
}

template <>
Allocator& getDefaultAllocator<Mallocator>() {
    static Mallocator defaultInstance;
    return defaultInstance;
}

} // namespace px
