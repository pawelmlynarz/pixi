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
    size_t heapSize_{0_B};
#if HEAP_ALLOCATOR_STATS
    size_t allocatedSize_{0_B};
#endif
    
#if PLATFORM_WINDOWS
    static constexpr size_t sMinTlsfAlign{16_B};
#else
#error Minimum alignment not specified for this platform.
#endif
};

HeapAllocator::HeapAllocator(size_t const heapSize) {
    memory_ = sysAlignedAllocate(heapSize, 16_B);
    heapSize_ = heapSize;

    tlsfHandle_ = tlsf_create_with_pool(memory_, heapSize);
}

HeapAllocator::~HeapAllocator() {
#if HEAP_ALLOCATOR_STATS
    pxEnsureMsgf(allocatedSize_ == 0, "Allocated size not zero. {} bytes was not freed when destroying the heap.", allocatedSize_);
#endif
    tlsf_destroy(tlsfHandle_);
    sysAlignedFree(memory_);
}

void* HeapAllocator::alloc(size_t const size) {
#if HEAP_ALLOCATOR_STATS
    void* const addr{ tlsf_memalign(tlsfHandle_, sMinTlsfAlign, size)};
    allocatedSize_ += tlsf_block_size( addr );
    return addr;
#else
    return tlsf_memalign(tlsfHandle_, sMinTlsfAlign, size);
#endif
}

void HeapAllocator::free(void* const addr) {
#if HEAP_ALLOCATOR_STATS
    allocatedSize_ -= tlsf_block_size( addr );
#else
    tlsf_free(tlsfHandle_, addr);
#endif
}

void* HeapAllocator::allocAligned(size_t const size, size_t const align) {
#if HEAP_ALLOCATOR_STATS
    void* const addr{ tlsf_memalign(tlsfHandle_, std::max(align, sMinTlsfAlign), size)};
    allocatedSize_ += tlsf_block_size( addr );
    return addr;
#else
    return tlsf_memalign(tlsfHandle_, std::max(align, sMinTlsfAlign), size);
#endif
}

void* HeapAllocator::realloc(void* const addr, size_t const size, bool /*preserve*/) {
#if HEAP_ALLOCATOR_STATS
    size_t const oldSize{ addr ? tlsf_block_size(addr) : 0 };
    void* const newAddr{ tlsf_realloc(tlsfHandle_, addr, size) };

    if (newAddr || size == 0) {
        allocatedSize_ -= oldSize;
        allocatedSize_ += size ? tlsf_block_size(newAddr) : 0;
    }

    return newAddr;
#else
    return tlsf_realloc(tlsfHandle_, addr, size);
#endif
}

void HeapAllocator::checkCorruption() {
    pxAssert(tlsf_check_pool(tlsf_get_pool(tlsfHandle_)) == 0);
}

Allocator* createHeapAllocator(size_t const heapSize) {
    return new HeapAllocator(heapSize);
}

} // namespace px
