// © 2026 Pawel Mlynarz

#pragma once

#include <mutex>

namespace px {

template <typename T>
concept BasicLockableC =
    requires(T lock) {
        { lock.lock() } noexcept -> std::same_as<void>;
        { lock.unlock() } noexcept -> std::same_as<void>;
    };

template <BasicLockableC... LockTs>
using ScopedLock = std::scoped_lock<LockTs...>;

} // namespace px
