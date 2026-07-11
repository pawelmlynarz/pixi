// © 2026 Pawel Mlynarz

// NOLINTBEGIN

#ifndef PX_DISABLE_MEMORY_MANAGEMENT

#include "memory/memory.h"
#include "memory/allocator.h"
#include "memory/mallocator.h"
#include "memory/heap_allocator.h"

#ifdef __clang__

int __cdecl preStaticsInitStartup() __attribute__((constructor(101)));

#elifdef _MSC_VER

int __cdecl preStaticsInitStartup();

#pragma section(".CRT$XIU", read)
extern "C" __declspec(allocate(".CRT$XIU")) int(__cdecl* _initAllocators)() = preStaticsInitStartup;

#endif

int __cdecl preStaticsInitStartup() {
    using namespace px;

    Memory::setDefaultAllocator(getDefaultAllocator<Mallocator>());

    Allocator* const heapAllocator{createHeapAllocator(defaultHeapSize)};

    // Locking allocator takes responsibility for destroying the heap, let's make it
    // static for calling destructor as we don't have an exit point.
    static LockingAllocator sLockingAllocator(heapAllocator);

    Memory::setDefaultAllocator(sLockingAllocator);

    return 0;
}

#endif

// NOLINTEND
