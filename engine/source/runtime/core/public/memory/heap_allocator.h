// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"
#include "units.h"

namespace px {

#define HEAP_ALLOCATOR_STATS WITH_EDITOR
#define HEAP_ALLOCATOR_TRACKING_STACKS WITH_EDITOR

constexpr size_t defaultHeapSize{256_MiB};

class HeapAllocator;

PXENGINE_API Allocator* createHeapAllocator(size_t heapSize);

} // namespace px
