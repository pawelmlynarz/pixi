// © 2026 Pawel Mlynarz

#pragma once

namespace px {

void* sysAlignedAllocate(size_t size, size_t alignment) noexcept;

void sysAlignedFree(void* ptr) noexcept;

} // namespace px
