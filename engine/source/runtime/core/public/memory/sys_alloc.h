// © 2026 Pawel Mlynarz

#pragma once

namespace px {

/**
 * Allocates memory directly from the OS/CRT, bypassing the engine's allocator system entirely. Intended for
 * allocators (e.g. HeapAllocator) to reserve their own backing storage.
 *
 * @param size Size, in bytes, of the block to allocate.
 * @param alignment Power-of-two alignment, in bytes, of the returned block.
 *
 * @return Pointer to the allocated block, or nullptr on failure.
 */
void* sysAlignedAllocate(size_t size, size_t alignment) noexcept;

/**
 * Frees a block of memory previously returned by sysAlignedAllocate().
 *
 * @param ptr Pointer to the block to free.
 */
void sysAlignedFree(void* ptr) noexcept;

} // namespace px
