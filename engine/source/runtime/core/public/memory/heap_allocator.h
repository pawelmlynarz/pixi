// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"
#include "units.h"

namespace px {

// Tracks live allocation count/size (and, if HEAP_ALLOCATOR_TRACKING_STACKS is set, per-allocation stack traces)
// for every HeapAllocator instance. Also asserted to be zero on destruction to catch leaks.
#define HEAP_ALLOCATOR_STATS WITH_EDITOR
#define HEAP_ALLOCATOR_TRACKING_STACKS WITH_EDITOR

// Default backing heap size used for the engine's main heap allocator.
constexpr size_t defaultHeapSize{256_MiB};

class HeapAllocator;

/**
 * Creates a TLSF-backed heap allocator over a fixed-size backing heap.
 *
 * @param heapSize Size, in bytes, of the backing heap to reserve.
 *
 * @return Pointer to the newly created allocator. Caller takes ownership.
 */
PXENGINE_API Allocator* createHeapAllocator(size_t heapSize);

} // namespace px
