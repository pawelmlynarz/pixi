// © 2026 Pawel Mlynarz

#pragma once

#include "tools/asserts.h"

#include <atomic>

namespace px {

#pragma warning(push)
// MSVC Complains about std::atomic<bool> not having dll interface, but it's a std type and doesn't need dll export.
#pragma warning(disable : 4251)

class PXENGINE_API SpinLock {
  public:
    enum : uint8_t {
        Unlocked = false,
        Locked = true
    };

    PX_NONCOPYABLE_NONMOVABLE(SpinLock);
    
    SpinLock() noexcept = default;
    ~SpinLock() {
        pxAssert(lock_.load(std::memory_order_acquire) == Unlocked);
    }

    void lock() noexcept {
        for (;;) {
            if (!lock_.exchange(true, std::memory_order_acquire)) {
                return;
            }

            while (lock_.load(std::memory_order_relaxed)) {
                pxToDo("Platform specific hint.");
                _mm_pause();
            }
        }
    }

    bool tryLock() noexcept {
        return !lock_.load(std::memory_order_relaxed) && !lock_.exchange(true, std::memory_order_acquire);
    }

    void unlock() noexcept {
        lock_.store(false, std::memory_order_release);
    }

  private:
    std::atomic<bool> lock_{Unlocked};
    static_assert(std::atomic<bool>::is_always_lock_free);
};

#pragma warning(pop)

} // namespace px
