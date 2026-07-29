// © 2026 Pawel Mlynarz

#include "memory/memory.h"
#include "memory/allocator.h"
#include "tools/asserts.h"
#include "tools/misc.h"

#include <memory>

namespace px {

namespace {

thread_local Allocator* sCurrentAllocator{nullptr};
Allocator* sDefaultAllocator{nullptr};
Allocator* sDebugAllocator{nullptr};

inline void setCurrentAllocator(Allocator* newAllocator) {
    sCurrentAllocator = newAllocator;
}

inline Allocator* getCurrentAllocator() {
    if (!sCurrentAllocator) {
        sCurrentAllocator = sDefaultAllocator;
    }
    return sCurrentAllocator;
}

} // namespace

void* Memory::alloc(size_t const size) {
    if (!size) [[unlikely]] {
        return nullptr;
    }

    Allocator* const alloc{getCurrentAllocator()};
    void* const ptr{alloc->alloc(size)};

    if (!ptr) [[unlikely]] {
        alloc->checkCorruption();
        pxAssertMsgf(false, "Out of memory, unable to satisfy request for %d bytes", size);
    }
    return ptr;
}

void* Memory::allocAligned(size_t const size, size_t const align) {
    if (!size) [[unlikely]] {
        return nullptr;
    }
    pxAssert(isPowerOfTwo(align));

    Allocator* const alloc{getCurrentAllocator()};
    void* const ptr{alloc->allocAligned(size, align)};

    if (!ptr) [[unlikely]] {
        alloc->checkCorruption();
        pxAssertMsgf(false, "Out of memory, unable to satisfy request for %d bytes with alignment %d", size, align);
    }
    return ptr;
}

void* Memory::realloc(void* const addr, size_t const size, bool const preserve) {
    if (!size) [[unlikely]] {
        free(addr);
        return nullptr;
    }

    if (!addr) [[unlikely]] {
        return alloc(size);
    }

    Allocator* const alloc{getCurrentAllocator()};
    void* const ptr{alloc->realloc(addr, size, preserve)};

    return ptr;
}

void Memory::free(void* const addr) {
    getCurrentAllocator()->free(addr);
}

Allocator& Memory::getDefaultAllocator() {
    return *sDefaultAllocator;
}

void Memory::setDefaultAllocator(Allocator& allocator) {
    sDefaultAllocator = &allocator;
    setCurrentAllocator(sDefaultAllocator);
}

Allocator& Memory::getDebugAllocator() {
    return *sDebugAllocator;
}

void Memory::setDebugAllocator(Allocator& allocator) {
    sDebugAllocator = &allocator;
}

Allocator& Memory::getCurrent() {
    return *getCurrentAllocator();
}

void Memory::setCurrent(Allocator& allocator) {
    setCurrentAllocator(&allocator);
}

} // namespace px
