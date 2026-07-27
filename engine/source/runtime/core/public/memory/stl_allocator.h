// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"

namespace px {

/**
 * Adapts an engine Allocator (via getDefaultAllocatorInstance<AllocatorT>()) to the standard library's Allocator
 * concept, so px containers and std containers alike can be backed by engine allocators.
 */
template <class DataT, class AllocatorT = class Mallocator>
class StlAllocator {
  public:
    using value_type = DataT;

    /**
     * Constructs an adapter bound to AllocatorT's default instance.
     */
    StlAllocator();

    template <class OtherDataT>
    StlAllocator(StlAllocator<OtherDataT, AllocatorT> const&);

    template <class OtherDataT, class OtherAllocatorT>
    StlAllocator(StlAllocator<OtherDataT, OtherAllocatorT> const&);

    StlAllocator& operator=(StlAllocator const&) { return *this; }

    template <class OtherDataT, class OtherAllocatorT>
    StlAllocator& operator=(StlAllocator<OtherDataT, OtherAllocatorT> const&) { return *this; }

    template <class OtherDataT, class OtherAllocatorT>
    friend inline bool operator==(StlAllocator<DataT, AllocatorT> const& lhs, StlAllocator<OtherDataT, OtherAllocatorT> const& rhs) {
        return &lhs.allocator_ == &rhs.allocator_;
    }

    /**
     * Allocates storage for the given number of elements.
     *
     * @param size Number of DataT elements to allocate storage for.
     *
     * @return Pointer to the allocated, uninitialized storage.
     */
    DataT* allocate(size_t size);

    /**
     * Frees storage previously returned by allocate().
     *
     * @param addr Pointer to the storage to free.
     * @param size Number of DataT elements the storage was allocated for.
     */
    void deallocate(DataT* addr, size_t size);

  private:
    template <class, class>
    friend class StlAllocator;

    Allocator& allocator_;
};

} // namespace px

#include "stl_allocator.inl"
