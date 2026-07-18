// © 2026 Pawel Mlynarz

#pragma once

#include "mallocator.h"

namespace px {

template <class DataT, class AllocatorT>
StlAllocator<DataT, AllocatorT>::StlAllocator()
    : allocator_(getDefaultInstance<AllocatorT>()) {}

template <class DataT, class AllocatorT>
template <class OtherDataT>
StlAllocator<DataT, AllocatorT>::StlAllocator(StlAllocator<OtherDataT, AllocatorT> const& other)
    : allocator_(other.allocator_) {}

template <class DataT, class AllocatorT>
template <class OtherDataT, class OtherAllocatorT>
StlAllocator<DataT, AllocatorT>::StlAllocator(StlAllocator<OtherDataT, OtherAllocatorT> const&)
    : allocator_(getDefaultInstance<OtherAllocatorT>()) {}

template <class DataT, class AllocatorT>
DataT* StlAllocator<DataT, AllocatorT>::allocate(size_t const size) {
    return static_cast<DataT*>(
        allocator_.allocAligned(size * sizeof(DataT), alignof(DataT))
    );
}

template <class DataT, class AllocatorT>
void StlAllocator<DataT, AllocatorT>::deallocate(DataT* addr, size_t) {
    allocator_.free(addr);
}

} // namespace px
