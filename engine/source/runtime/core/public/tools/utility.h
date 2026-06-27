// © 2026 Pawel Mlynarz

#pragma once

#include "tools/asserts.h"

#include <utility>
#include <memory>
#include <ranges>
#include <vector>

namespace px {

template <typename T, typename TDeleter = std::default_delete<T>>
using UniquePtr = std::unique_ptr<T, TDeleter>;

template <typename T>
using WeakPtr = std::weak_ptr<T>;

template <typename T, typename... TArgs>
    requires std::constructible_from<T, TArgs...>
std::unique_ptr<T> makeUnique(TArgs&&... args) {
    return std::make_unique<T>(std::forward<TArgs>(args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename... TArgs>
    requires std::constructible_from<T, TArgs...>
std::shared_ptr<T> makeShared(TArgs&&... args) {
    return std::make_shared<T>(std::forward<TArgs>(args)...);
}

constexpr bool sharedRefNoexcept{
#ifdef DO_CHECK
    false
#else
    true
#endif
};

template <typename T>
class SharedRef {
  public:
    SharedRef() = delete;

    SharedRef(SharedPtr<T> const& ptr) noexcept(sharedRefNoexcept)
        : ptr_(ptr) {
        pxAssertMsgf(ptr_, "SharedRef constructed with null pointer");
    }

    SharedRef(SharedPtr<T>&& ptr) noexcept(sharedRefNoexcept)
        : ptr_(std::move(ptr)) {
        pxAssertMsgf(ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U> const& ptr) noexcept(sharedRefNoexcept)
        : ptr_(ptr) {
        pxAssertMsgf(ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U>&& ptr) noexcept(sharedRefNoexcept)
        : ptr_(std::move(ptr)) {
        pxAssertMsgf(ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedRef<U> const& other) noexcept(sharedRefNoexcept)
        : ptr_(other.toPtr()) {
        pxAssertMsgf(ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef& operator=(SharedRef<U> const& other) noexcept(sharedRefNoexcept) {
        ptr_ = other.ToPtr();
        pxAssertMsgf(ptr_, "SharedRef assigned null pointer");
        return *this;
    }

    SharedRef(SharedRef const&) = default;
    SharedRef& operator=(SharedRef const&) = default;

    SharedRef(SharedRef&&) noexcept = default;
    SharedRef& operator=(SharedRef&&) noexcept = default;

    T& operator*() const noexcept {
        return *ptr_;
    }

    T* operator->() const noexcept {
        return ptr_.get();
    }

    T* get() const noexcept {
        return ptr_.get();
    }

    SharedPtr<T> toPtr() const noexcept {
        return ptr_;
    }

    WeakPtr<T> toWeak() const noexcept {
        return ptr_;
    }

  private:
    SharedPtr<T> ptr_;
};

template <typename T>
inline bool operator==(SharedRef<T> const& a, SharedRef<T> const& b) noexcept {
    return a.get() == b.get();
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedPtr<TTo> staticCastSharedPtr(SharedPtr<TFrom> const& ptr) noexcept {
    return std::static_pointer_cast<TTo>(ptr);
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> staticCastSharedRef(SharedPtr<TFrom> const& ptr) noexcept(sharedRefNoexcept) {
    return SharedRef<TTo>(std::static_pointer_cast<TTo>(ptr));
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> staticCastSharedRef(SharedRef<TFrom> const& ref) noexcept(sharedRefNoexcept) {
    static_assert(std::is_base_of_v<TFrom, TTo>, "Can't static cast to a type that doesn't derive from TFrom.");
    return SharedRef<TTo>(std::static_pointer_cast<TTo>(ref.toPtr()));
}

template <typename T>
using EnableSharedFromThis = std::enable_shared_from_this<T>;

template <class T>
[[nodiscard]] static SharedRef<T> sharedThis(T* const thisPtr) {
    return staticCastSharedRef<T>(thisPtr->shared_from_this());
}

template <class T>
[[nodiscard]] static SharedRef<T> sharedThis(T const* const thisPtr) {
    return StaticCastSharedRef<T const>(thisPtr->shared_from_this());
}

template <std::integral T, std::integral A>
[[nodiscard]]
constexpr T alignUp(T actualSize, A alignment) noexcept {
    return static_cast<T>(
        (static_cast<size_t>(actualSize) + static_cast<size_t>(alignment) - 1) & ~(static_cast<size_t>(alignment) - 1)
    );
}

template <std::ranges::sized_range R>
[[nodiscard]]
constexpr auto countOf(R const& range) noexcept {
    return std::ranges::size(range);
}

template <typename T>
[[nodiscard]]
constexpr size_t getByteSizeOf(std::vector<T> const& vec) noexcept {
    return vec.size() * sizeof(T);
}

template <typename TEnum>
constexpr auto enumCast(TEnum const enumValue) noexcept {
    return static_cast<__underlying_type(TEnum)>(enumValue);
}

template <typename TEnum>
constexpr auto asEnum(auto const enumValueInt) noexcept {
    return static_cast<TEnum>(enumValueInt);
}

} // namespace px

// NOLINTBEGIN

namespace std {

template <typename T>
struct hash<px::SharedRef<T>> {
    size_t operator()(px::SharedRef<T> const& Ref) const noexcept {
        return std::hash<T*>{}(Ref.get());
    }
};

// NOLINTEND

} // namespace std
