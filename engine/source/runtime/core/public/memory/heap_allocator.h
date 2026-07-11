// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"
#include "units.h"

namespace px {

constexpr size_t defaultHeapSize{256_MiB};

class HeapAllocator;

PXENGINE_API Allocator* createHeapAllocator(size_t heapSize);

} // namespace px
