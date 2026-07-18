// © 2026 Pawel Mlynarz

#pragma once

#include "tools/compiler.h"
#include "tools/misc.h"

#define LOCKING_ALLOCATOR_USE_SPINLOCK 1

#if LOCKING_ALLOCATOR_USE_SPINLOCK

#include "threading/spin_lock.h"
using LockingAllocatorLock = px::SpinLock;

#else

#include "threading/mutex.h"
using LockingAllocatorLock = px::Mutex;

#endif

namespace px {

struct PXENGINE_API Allocator {
    virtual ~Allocator() = default;

    virtual void* alloc(size_t size) = 0;
    virtual void free(void* addr) = 0;
    virtual void* allocAligned(size_t size, size_t align) = 0;
    virtual void* realloc(void* addr, size_t size, bool preserve = true) = 0;

    virtual void checkCorruption() {}
};

template <typename AllocatorT>
Allocator& getDefaultInstance() = delete;

class PXENGINE_API LockingAllocator final : public Allocator {
  public:
    LockingAllocator(Allocator* allocator);
    ~LockingAllocator() override;

    void* alloc(size_t size) override;
    void free(void* addr) override;
    void* allocAligned(size_t size, size_t align) override;
    void* realloc(void* addr, size_t size, bool preserve = true) override;
    void checkCorruption() override;

  private:
    Allocator* allocator_{nullptr};
    LockingAllocatorLock lock_;
};

class PXENGINE_API AllocatorScopeOverride {
  public:
    AllocatorScopeOverride(Allocator& allocator);
    ~AllocatorScopeOverride();

    PX_NONCOPYABLE_NONMOVABLE(AllocatorScopeOverride)

  private:
    Allocator& oldAllocator_;
};

} // namespace px
