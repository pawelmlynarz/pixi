// © 2026 Pawel Mlynarz

#include "memory/heap_allocator.h"
#include "tools/asserts.h"
#include "tlsf.h"

#ifdef _MSC_VER
#include <malloc.h>
#endif

namespace px {

namespace {

inline void* sysAlignedAllocate(size_t size, size_t alignment) noexcept {
#ifdef _MSC_VER
    return _aligned_malloc(size, alignment);
#else
#error Compiler not supported.
#endif
}

inline void sysAlignedFree(void* ptr) noexcept {
#ifdef _MSC_VER
    _aligned_free(ptr);
#else
#error Compiler not supported.
#endif
}

} // namespace

class HeapAllocator final : public Allocator {
  public:
    explicit HeapAllocator(size_t heapSize);
    ~HeapAllocator() override;

    void* alloc(size_t size) override;
    void free(void* addr) override;
    void* allocAligned(size_t size, size_t align) override;
    void* realloc(void* addr, size_t size, bool preserve = true) override;
    void checkCorruption() override;

  private:
    void* memory_{nullptr};
    tlsf_t tlsfHandle_{nullptr};
    size_t size_{0};

#if PLATFORM_WINDOWS
    static constexpr size_t sMinTlsfAlign{16_B};
#else
#error Minimum alignment not specified for this platform.
#endif
};

HeapAllocator::HeapAllocator(size_t const heapSize) {
    memory_ = sysAlignedAllocate(heapSize, 16_B);
    size_ = heapSize;

    tlsfHandle_ = tlsf_create_with_pool(memory_, heapSize);
}

HeapAllocator::~HeapAllocator() {
    tlsf_destroy(tlsfHandle_);
    sysAlignedFree(memory_);
}

void* HeapAllocator::alloc(size_t const size) {
    return tlsf_memalign(tlsfHandle_, sMinTlsfAlign, size);
}

void HeapAllocator::free(void* const addr) {
    tlsf_free(tlsfHandle_, addr);
}

void* HeapAllocator::allocAligned(size_t const size, size_t const align) {
    return tlsf_memalign(tlsfHandle_, std::max(align, sMinTlsfAlign), size);
}

void* HeapAllocator::realloc(void* const addr, size_t const size, bool /*preserve*/) {
    return tlsf_realloc(tlsfHandle_, addr, size);
}

void HeapAllocator::checkCorruption() {
    pxAssert(tlsf_check_pool(tlsf_get_pool(tlsfHandle_)) == 0);
}

Allocator* createHeapAllocator(size_t const heapSize) {
    return new HeapAllocator(heapSize);
}

} // namespace px
