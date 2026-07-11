// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"

namespace px {

class Mallocator;

template <>
PXENGINE_API Allocator& getDefaultAllocator<Mallocator>();

} // namespace px
