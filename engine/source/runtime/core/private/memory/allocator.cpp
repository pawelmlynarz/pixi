// © 2026 Pawel Mlynarz

#include "memory/allocator.h"
#include "memory/memory.h"

namespace px {

AllocatorScopeOverride::AllocatorScopeOverride(Allocator& allocator)
    : oldAllocator_(Memory::getCurrent()) {
    Memory::setCurrent(allocator);
}

AllocatorScopeOverride::~AllocatorScopeOverride() {
    Memory::setCurrent(oldAllocator_);
}

} // namespace px
