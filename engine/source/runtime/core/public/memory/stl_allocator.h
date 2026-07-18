// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"

namespace px {

template <class DataT, class AllocatorT = class Mallocator>
class StlAllocator {
  public:
    using value_type = DataT;

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

    DataT* allocate(size_t size);

    void deallocate(DataT* addr, size_t size);

  private:
    template <class, class>
    friend class StlAllocator;

    Allocator& allocator_;
};

} // namespace px

#include "stl_allocator.inl"
