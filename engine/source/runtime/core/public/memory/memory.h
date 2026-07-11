// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

namespace px {

struct Allocator;

struct PXENGINE_API Memory {
    // Allocate a block of memory, return nullptr on failure.
    static void* alloc(size_t size);

    // Allocate a block of memory aligned to a given power-of-two number of bytes
    static void* allocAligned(size_t size, size_t align);

    // Attempt to extend an existing allocation or allocate a new block of memory.
    static void* realloc(void* addr, size_t size, bool preserve = true);

    // Free a block of previously allocated memory.
    static void free(void* addr);

    // Get the default allocator.
    static Allocator& getDefaultAllocator();

    // Set the default allocator.
    static void setDefaultAllocator(Allocator& allocator);

    // Get the current allocator.
    static Allocator& getCurrent();

    // Set the current allocator.
    static void setCurrent(Allocator& allocator);
};

} // namespace px
