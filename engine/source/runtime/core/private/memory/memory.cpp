// © 2026 Pawel Mlynarz

#include "memory/memory.h"
#include "memory/allocator.h"
#include "tools/asserts.h"
#include "tools/misc.h"

#include <memory>

namespace px {

namespace {

thread_local Allocator* currentAllocator{nullptr};
Allocator* defaultAllocator{nullptr};
Allocator* debugAllocator{nullptr};

inline void setCurrentAllocator(Allocator* newAllocator) {
    currentAllocator = newAllocator;
}

inline Allocator* getCurrentAllocator() {
    if (!currentAllocator) {
        currentAllocator = defaultAllocator;
    }
    return currentAllocator;
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
    return *defaultAllocator;
}

void Memory::setDefaultAllocator(Allocator& allocator) {
    defaultAllocator = &allocator;
    setCurrentAllocator(defaultAllocator);
}

Allocator& Memory::getDebugAllocator() {
    return *debugAllocator;
}

void Memory::setDebugAllocator(Allocator& allocator) {
    debugAllocator = &allocator;
}

Allocator& Memory::getCurrent() {
    return *getCurrentAllocator();
}

void Memory::setCurrent(Allocator& allocator) {
    setCurrentAllocator(&allocator);
}

} // namespace px
