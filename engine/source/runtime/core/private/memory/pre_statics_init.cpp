// © 2026 Pawel Mlynarz

// NOLINTBEGIN

#ifndef PX_DISABLE_MEMORY_MANAGEMENT

#include "memory/memory.h"
#include "memory/allocator.h"
#include "memory/mallocator.h"
#include "memory/heap_allocator.h"

namespace {

px::LockingAllocator* sHeapAllocator{nullptr};

} // namespace

#ifdef __clang__

int __cdecl preStaticsInit() __attribute__((constructor(101)));

#elifdef _MSC_VER

int __cdecl preStaticsInit();

#pragma section(".CRT$XIU", read)
extern "C" __declspec(allocate(".CRT$XIU")) int(__cdecl* _initAllocators)() = preStaticsInit;

#endif

void __cdecl postStaticsDestructed();

int __cdecl preStaticsInit() {
    using namespace px;

    Memory::setDefaultAllocator(getDefaultInstance<Mallocator>());
    Memory::setDebugAllocator(getDefaultInstance<Mallocator>());

    Allocator* const heapAllocator{createHeapAllocator(defaultHeapSize)};

    std::atexit(postStaticsDestructed);
    sHeapAllocator = new LockingAllocator(heapAllocator);

    Memory::setDefaultAllocator(*sHeapAllocator);

    return 0;
}

void __cdecl postStaticsDestructed() {
    delete sHeapAllocator;
}

#endif

// NOLINTEND
