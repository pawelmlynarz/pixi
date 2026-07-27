// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"

namespace px {

// Allocator backed directly by the CRT's aligned malloc/free/realloc. Used as the engine's bootstrap
// allocator, before the heap allocator is available, and as a fallback default instance.
class Mallocator;

template <>
PXENGINE_API Allocator& getDefaultAllocatorInstance<Mallocator>();

} // namespace px
