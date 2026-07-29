// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"
#include "tools/misc.h"

namespace px {

/**
 * Abstract allocator interface implemented by every allocator in the engine (heap, malloc-backed, locking, etc.).
 */
struct PX_ENGINE_API Allocator {
    virtual ~Allocator() = default;

    /**
     * Allocates a block of memory.
     *
     * @param size Size, in bytes, of the block to allocate.
     *
     * @return Pointer to the allocated block, or nullptr on failure.
     */
    virtual void* alloc(size_t size) = 0;

    /**
     * Frees a block of memory.
     *
     * @param addr Pointer to the block to free.
     */
    virtual void free(void* addr) = 0;

    /**
     * Allocates a block of memory aligned to a given power-of-two number of bytes.
     *
     * @param size Size, in bytes, of the block to allocate.
     * @param align Power-of-two alignment, in bytes, of the returned block.
     *
     * @return Pointer to the allocated block, or nullptr on failure.
     */
    virtual void* allocAligned(size_t size, size_t align) = 0;

    /**
     * Attempts to extend an existing allocation in place, or allocates a new block and copies the contents over.
     *
     * @param addr Pointer to the block to reallocate.
     * @param size New size, in bytes, of the block.
     * @param preserve True to preserve the existing contents of the block.
     *
     * @return Pointer to the reallocated block, or nullptr on failure.
     */
    virtual void* realloc(void* addr, size_t size, bool preserve = true) = 0;

    /**
     * Validates the internal consistency of the allocator, asserting if corruption is detected.
     */
    virtual void checkCorruption() {}
};

/**
 * Returns the default, shared instance of the given allocator type. Must be explicitly specialized for each
 * allocator type that supports being used as a default instance (see Mallocator).
 */
template <typename AllocatorT>
Allocator& getDefaultAllocatorInstance() = delete;

/**
 * RAII scope guard that overrides Memory's current allocator for its lifetime, restoring the previous
 * allocator on destruction.
 */
class PX_ENGINE_API AllocatorScopeOverride final : NonCopyableNonMovable {
  public:
    AllocatorScopeOverride(Allocator& allocator);
    
    ~AllocatorScopeOverride();

  private:
    Allocator& oldAllocator_;
};

} // namespace px
