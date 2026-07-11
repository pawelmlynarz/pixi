// © 2026 Pawel Mlynarz

#pragma once

#include <bit>

namespace px {

// NOLINTBEGIN(bugprone-macro-parentheses)

#define PX_NONCOPYABLE(T) \
    T(T const&) = delete; \
    T& operator=(T const&) = delete;

#define PX_NONCOPYABLE_NONMOVABLE(T) \
    PX_NONCOPYABLE(T)                \
    T(T&&) = delete;                 \
    T& operator=(T&&) = delete;

// NOLINTEND(bugprone-macro-parentheses)

constexpr bool isPowerOfTwo(size_t const value) noexcept {
    return std::has_single_bit(value);
}

class NonCopyable {
  protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

  public:
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;

    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};

class NonMovable {
  protected:
    NonMovable() = default;
    ~NonMovable() = default;

  public:
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

class NonCopyableNonMovable : NonCopyable, NonMovable {
  protected:
    NonCopyableNonMovable() = default;
    ~NonCopyableNonMovable() = default;
};

} // namespace px
