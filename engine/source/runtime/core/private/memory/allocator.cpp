// © 2026 Pawel Mlynarz

#include "memory/allocator.h"
#include "memory/mallocator.h"
#include "memory/memory.h"
#include "threading/scoped_lock.h"

namespace px {

LockingAllocator::LockingAllocator(Allocator* allocator)
    : allocator_(allocator) {
}

LockingAllocator::~LockingAllocator() {
    Memory::setDefaultAllocator(getDefaultInstance<Mallocator>());
    delete allocator_;
}

void* LockingAllocator::alloc(size_t const size) {
    ScopedLock const scopeLock(lock_);
    return allocator_->alloc(size);
}

void LockingAllocator::free(void* const addr) {
    ScopedLock const scopeLock(lock_);
    allocator_->free(addr);
}

void* LockingAllocator::allocAligned(size_t const size, size_t const align) {
    ScopedLock const scopeLock(lock_);
    return allocator_->allocAligned(size, align);
}

void* LockingAllocator::realloc(void* const addr, size_t const size, bool const preserve) {
    ScopedLock const scopeLock(lock_);
    return allocator_->realloc(addr, size, preserve);
}

void LockingAllocator::checkCorruption() {
    ScopedLock const scopeLock(lock_);
    allocator_->checkCorruption();
}

AllocatorScopeOverride::AllocatorScopeOverride(Allocator& allocator)
    : oldAllocator_(Memory::getCurrent()) {
    Memory::setCurrent(allocator);
}

AllocatorScopeOverride::~AllocatorScopeOverride() {
    Memory::setCurrent(oldAllocator_);
}

} // namespace px
