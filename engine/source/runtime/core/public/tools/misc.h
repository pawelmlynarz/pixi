// © 2026 Pawel Mlynarz

#pragma once

#include <bit>

namespace px {

constexpr bool isPowerOfTwo(size_t const value) noexcept {
    return std::has_single_bit(value);
}

class PX_ENGINE_API NonCopyable {
  protected:
    NonCopyable() = default;
    ~NonCopyable() = default;

  public:
    NonCopyable(NonCopyable const&) = delete;
    NonCopyable& operator=(NonCopyable const&) = delete;

    NonCopyable(NonCopyable&&) = delete;
    NonCopyable& operator=(NonCopyable&&) = delete;
};

class PX_ENGINE_API NonMovable {
  protected:
    NonMovable() = default;
    ~NonMovable() = default;

  public:
    NonMovable(NonMovable&&) = delete;
    NonMovable& operator=(NonMovable&&) = delete;
};

class PX_ENGINE_API NonCopyableNonMovable : NonCopyable, NonMovable {
  protected:
    NonCopyableNonMovable() = default;
    ~NonCopyableNonMovable() = default;
};

} // namespace px
