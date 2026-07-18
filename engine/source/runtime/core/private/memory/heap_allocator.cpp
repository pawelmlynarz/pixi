// © 2026 Pawel Mlynarz

#include "memory/heap_allocator.h"
#include "memory/sys_alloc.h"
#include "tools/asserts.h"
#include "tlsf.h"
#include "tools/stack_trace.h"

#include <unordered_set>
#include <ranges>

namespace px {

namespace {

#if HEAP_ALLOCATOR_STATS

struct AllocRecord {
    using hash_t = uint32;
    void const* addr{nullptr};
    hash_t hash{0U};
    size_t allocatedSize{0_B};
    StackTrace stackTrace;
};

struct AllocTracker {
    size_t allocatedCount{0U};
    size_t allocatedSize{0_B};

    using pair_t = std::pair<void const* const, AllocRecord>;

    using AllocRecordsMap_t =
        std::unordered_map<
            void const*, AllocRecord,
            std::hash<void const*>, std::equal_to<>, StlAllocator<pair_t>>;

    AllocRecordsMap_t records;

    void add(void const* addr, size_t const size) {
        StackTrace stackTrace{captureStackTrace(2, 6)};
        AllocRecord& record{records[addr]};
        record.addr = addr;
        record.hash = stackTrace._Get_hash();
        record.allocatedSize = size;
        record.stackTrace = std::move(stackTrace);
    }

    void remove(void const* addr) {
        records.erase(addr);
    }

    void reportStacks() {
        std::unordered_set<AllocRecord::hash_t> uniqueHashes;

        auto uniqueRecords{
            records | std::views::values | std::views::filter([&](AllocRecord const& record) {
                return uniqueHashes.insert(record.hash).second;
            })
        };

        for (auto const& record : uniqueRecords) {
            (void)fprintf(stderr, "Address: %p, Size: %llu bytes, Stack Trace:\n", record.addr, record.allocatedSize);
            printStackTraceToString(record.stackTrace);
        }
    }
};

#endif

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

#if PLATFORM_WINDOWS
    static constexpr size_t sMinTlsfAlign{16_B};
#else
#error Minimum alignment not specified for this platform.
#endif

#if HEAP_ALLOCATOR_STATS
    AllocTracker allocTracker_;
#endif
};

HeapAllocator::HeapAllocator(size_t const heapSize) {
    memory_ = sysAlignedAllocate(heapSize, 16_B);
    heapSize_ = heapSize;

    tlsfHandle_ = tlsf_create_with_pool(memory_, heapSize);
}

HeapAllocator::~HeapAllocator() {
#if HEAP_ALLOCATOR_STATS
    pxEnsureMsgf(allocTracker_.allocatedCount == 0, "Allocation count not zero. {} allocations were not freed, totalling in {} bytes.", allocTracker_.allocatedCount, allocTracker_.allocatedSize);
#endif
    tlsf_destroy(tlsfHandle_);
    sysAlignedFree(memory_);
}

void* HeapAllocator::alloc(size_t const size) {
#if HEAP_ALLOCATOR_STATS
    void* const addr{tlsf_memalign(tlsfHandle_, sMinTlsfAlign, size)};
    size_t const allocatedSize{tlsf_block_size(addr)};
    allocTracker_.allocatedSize += allocatedSize;
    ++allocTracker_.allocatedCount;
#if HEAP_ALLOCATOR_TRACKING_STACKS
    allocTracker_.add(addr, allocatedSize);
#endif
    return addr;
#else
    return tlsf_memalign(tlsfHandle_, sMinTlsfAlign, size);
#endif
}

void HeapAllocator::free(void* const addr) {
#if HEAP_ALLOCATOR_STATS
    size_t const freedSize{tlsf_block_size(addr)};
    allocTracker_.allocatedSize -= freedSize;
    --allocTracker_.allocatedCount;
#if HEAP_ALLOCATOR_TRACKING_STACKS
    allocTracker_.remove(addr);
#endif
#else
    tlsf_free(tlsfHandle_, addr);
#endif
}

void* HeapAllocator::allocAligned(size_t const size, size_t const align) {
#if HEAP_ALLOCATOR_STATS
    void* const addr{tlsf_memalign(tlsfHandle_, std::max(align, sMinTlsfAlign), size)};
    size_t const allocatedSize{tlsf_block_size(addr)};
    allocTracker_.allocatedSize += allocatedSize;
    ++allocTracker_.allocatedCount;
#if HEAP_ALLOCATOR_TRACKING_STACKS
    allocTracker_.add(addr, allocatedSize);
#endif
    return addr;
#else
    return tlsf_memalign(tlsfHandle_, std::max(align, sMinTlsfAlign), size);
#endif
}

void* HeapAllocator::realloc(void* const addr, size_t const size, bool /*preserve*/) {
#if HEAP_ALLOCATOR_STATS
    size_t const oldSize{addr ? tlsf_block_size(addr) : 0};
    void* const newAddr{tlsf_realloc(tlsfHandle_, addr, size)};

    if (newAddr || size == 0) {
        allocTracker_.allocatedSize -= oldSize;
        allocTracker_.allocatedSize += size ? tlsf_block_size(newAddr) : 0;
    }
#if HEAP_ALLOCATOR_TRACKING_STACKS
    allocTracker_.remove(addr);
    allocTracker_.add(newAddr, size);
#endif
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
