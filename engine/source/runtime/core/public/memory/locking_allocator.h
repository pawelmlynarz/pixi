// © 2026 Pawel Mlynarz

#pragma once

#include "allocator.h"
#include "tools/compiler.h"

#define LOCKING_ALLOCATOR_USE_SPINLOCK 1

#if LOCKING_ALLOCATOR_USE_SPINLOCK

#include "threading/spin_lock.h"
using LockingAllocatorLock = px::SpinLock;

#else

#include "threading/mutex.h"
using LockingAllocatorLock = px::Mutex;

#endif

namespace px {

/**
 * Wraps another allocator and serializes access to it behind a lock, making it safe to call from multiple threads.
 */
class PXENGINE_API LockingAllocator final : public Allocator {
  public:
    /**
     * Constructs the locking allocator around another allocator, taking ownership of it.
     *
     * @param allocator The allocator to wrap. Destroyed alongside this object.
     */
    LockingAllocator(Allocator* allocator);
    
    /**
     * Deletes the owned allocator.
     */
    ~LockingAllocator() override;

    // ~Allocator Begin

    void* alloc(size_t size) override;
    void free(void* addr) override;
    void* allocAligned(size_t size, size_t align) override;
    void* realloc(void* addr, size_t size, bool preserve = true) override;
    void checkCorruption() override;

    // ~Allocator End

  private:
    Allocator* allocator_{nullptr};
    LockingAllocatorLock lock_;
};

} // namespace px
