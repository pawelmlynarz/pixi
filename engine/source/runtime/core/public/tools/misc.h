// © 2026 Pawel Mlynarz

#pragma once

namespace px {

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
