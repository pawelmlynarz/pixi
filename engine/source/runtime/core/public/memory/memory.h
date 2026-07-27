// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"

namespace px {

struct Allocator;

/**
 * Engine-wide entry point for all memory allocation. Routes every request to the current allocator
 * (thread-local, see getCurrent()/setCurrent()), which defaults to the default allocator.
 */
struct PXENGINE_API Memory {
    /**
     * Allocates a block of memory using the current allocator.
     *
     * @param size Size, in bytes, of the block to allocate.
     *
     * @return Pointer to the allocated block, or nullptr if size is zero.
     */
    static void* alloc(size_t size);

    /**
     * Allocates a block of memory aligned to a given power-of-two number of bytes, using the current allocator.
     *
     * @param size Size, in bytes, of the block to allocate.
     * @param align Power-of-two alignment, in bytes, of the returned block.
     *
     * @return Pointer to the allocated block, or nullptr if size is zero.
     */
    static void* allocAligned(size_t size, size_t align);

    /**
     * Attempts to extend an existing allocation, or allocates a new block of memory, using the current allocator.
     *
     * @param addr Pointer to the block to reallocate. If nullptr, behaves like alloc().
     * @param size New size, in bytes, of the block. If zero, frees addr and returns nullptr.
     * @param preserve True to preserve the existing contents of the block.
     *
     * @return Pointer to the reallocated block, or nullptr if size is zero.
     */
    static void* realloc(void* addr, size_t size, bool preserve = true);

    /**
     * Frees a block of previously allocated memory using the current allocator.
     *
     * @param addr Pointer to the block to free.
     */
    static void free(void* addr);

    /**
     * @return The engine's default allocator.
     */
    static Allocator& getDefaultAllocator();

    /**
     * Sets the engine's default allocator, and makes it the current allocator.
     *
     * @param allocator The allocator to use as the default.
     */
    static void setDefaultAllocator(Allocator& allocator);

    /**
     * @return The engine's debug allocator, used for diagnostic/tooling allocations.
     */
    static Allocator& getDebugAllocator();

    /**
     * Sets the engine's debug allocator.
     *
     * @param allocator The allocator to use for debug allocations.
     */
    static void setDebugAllocator(Allocator& allocator);

    /**
     * @return The allocator currently in effect on this thread (see AllocatorScopeOverride).
     */
    static Allocator& getCurrent();

    /**
     * Sets the allocator currently in effect on this thread.
     *
     * @param allocator The allocator to make current.
     */
    static void setCurrent(Allocator& allocator);
};

} // namespace px
