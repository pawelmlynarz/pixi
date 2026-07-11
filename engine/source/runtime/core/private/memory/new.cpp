// © 2026 Pawel Mlynarz

#include "memory/memory.h"

#include <vcruntime_new.h>

#ifndef PX_DISABLE_MEMORY_MANAGEMENT

void* operator new(size_t const size) {
    return px::Memory::alloc(size);
}

void* operator new[](size_t const size) {
    return px::Memory::alloc(size);
}

void* operator new(size_t const size, std::align_val_t const alignment) {
    return px::Memory::allocAligned(size, static_cast<size_t>(alignment));
}

void* operator new[](size_t const size, std::align_val_t const alignment) {
    return px::Memory::allocAligned(size, static_cast<size_t>(alignment));
}

void* operator new(size_t const size, std::nothrow_t const&) noexcept {
    return px::Memory::alloc(size);
}

void* operator new[](size_t const size, std::nothrow_t const&) noexcept {
    return px::Memory::alloc(size);
}

void* operator new(size_t const size, std::align_val_t const alignment, std::nothrow_t const&) noexcept {
    return px::Memory::allocAligned(size, static_cast<size_t>(alignment));
}

void* operator new[](size_t const size, std::align_val_t const alignment, std::nothrow_t const&) noexcept {
    return px::Memory::allocAligned(size, static_cast<size_t>(alignment));
}

void operator delete(void* addr) noexcept {
    px::Memory::free(addr);
}

void operator delete[](void* addr) noexcept {
    px::Memory::free(addr);
}

void operator delete(void* addr, size_t) noexcept {
    px::Memory::free(addr);
}

void operator delete[](void* addr, size_t) noexcept {
    px::Memory::free(addr);
}

void operator delete(void* addr, std::align_val_t) noexcept {
    px::Memory::free(addr);
}

void operator delete[](void* addr, std::align_val_t) noexcept {
    px::Memory::free(addr);
}

void operator delete(void* addr, size_t, std::align_val_t) noexcept {
    px::Memory::free(addr);
}

void operator delete[](void* addr, size_t, std::align_val_t) noexcept {
    px::Memory::free(addr);
}

#endif
