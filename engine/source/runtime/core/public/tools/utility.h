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
std::unique_ptr<T> MakeUnique(TArgs&&... Args) {
    return std::make_unique<T>(std::forward<TArgs>(Args)...);
}

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template <typename T, typename... TArgs>
    requires std::constructible_from<T, TArgs...>
std::shared_ptr<T> MakeShared(TArgs&&... Args) {
    return std::make_shared<T>(std::forward<TArgs>(Args)...);
}

constexpr bool SharedRefNoexcept{
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

    SharedRef(SharedPtr<T> const& Ptr) noexcept(SharedRefNoexcept)
        : Ptr_(Ptr) {
        AssertMsgf(Ptr_, "SharedRef constructed with null pointer");
    }

    SharedRef(SharedPtr<T>&& Ptr) noexcept(SharedRefNoexcept)
        : Ptr_(std::move(Ptr)) {
        AssertMsgf(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U> const& Ptr) noexcept(SharedRefNoexcept)
        : Ptr_(Ptr) {
        AssertMsgf(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U>&& Ptr) noexcept(SharedRefNoexcept)
        : Ptr_(std::move(Ptr)) {
        AssertMsgf(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedRef<U> const& Other) noexcept(SharedRefNoexcept)
        : Ptr_(Other.ToPtr()) {
        AssertMsgf(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef& operator=(SharedRef<U> const& Other) noexcept(SharedRefNoexcept) {
        Ptr_ = Other.ToPtr();
        AssertMsgf(Ptr_, "SharedRef assigned null pointer");
        return *this;
    }

    SharedRef(SharedRef const&) = default;
    SharedRef& operator=(SharedRef const&) = default;

    SharedRef(SharedRef&&) noexcept = default;
    SharedRef& operator=(SharedRef&&) noexcept = default;

    T& operator*() const noexcept {
        return *Ptr_;
    }

    T* operator->() const noexcept {
        return Ptr_.get();
    }

    T* Get() const noexcept {
        return Ptr_.get();
    }

    SharedPtr<T> ToPtr() const noexcept {
        return Ptr_;
    }

    WeakPtr<T> ToWeak() const noexcept {
        return Ptr_;
    }

  private:
    SharedPtr<T> Ptr_;
};

template <typename T>
inline bool operator==(SharedRef<T> const& A, SharedRef<T> const& B) noexcept {
    return A.Get() == B.Get();
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedPtr<TTo> StaticCastSharedPtr(SharedPtr<TFrom> const& Ptr) noexcept {
    return std::static_pointer_cast<TTo>(Ptr);
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> StaticCastSharedRef(SharedPtr<TFrom> const& Ptr) noexcept(SharedRefNoexcept) {
    return SharedRef<TTo>(std::static_pointer_cast<TTo>(Ptr));
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> StaticCastSharedRef(SharedRef<TFrom> const& Ref) noexcept(SharedRefNoexcept) {
    return SharedRef<TTo>(std::static_pointer_cast<TTo>(Ref.ToPtr()));
}

template <typename T>
using EnableSharedFromThis = std::enable_shared_from_this<T>;

template <class T>
[[nodiscard]] static SharedRef<T> SharedThis(T* const ThisPtr) {
    return StaticCastSharedRef<T>(ThisPtr->shared_from_this());
}

template <class T>
[[nodiscard]] static SharedRef<T> SharedThis(T const* const ThisPtr) {
    return StaticCastSharedRef<T const>(ThisPtr->shared_from_this());
}

template <std::integral T, std::integral A>
[[nodiscard]]
constexpr T AlignUp(T ActualSize, A Alignment) noexcept {
    return static_cast<T>(
        (static_cast<size_t>(ActualSize) + static_cast<size_t>(Alignment) - 1) & ~(static_cast<size_t>(Alignment) - 1)
    );
}

template <std::ranges::sized_range R>
[[nodiscard]]
constexpr auto CountOf(R const& Range) noexcept {
    return std::ranges::size(Range);
}

template <typename T>
[[nodiscard]]
constexpr size_t GetByteSizeOf(std::vector<T> const& Vec) noexcept {
    return Vec.size() * sizeof(T);
}

} // namespace px

// NOLINTBEGIN

namespace std {

template <typename T>
struct hash<px::SharedRef<T>> {
    size_t operator()(px::SharedRef<T> const& Ref) const noexcept {
        return std::hash<T*>{}(Ref.Get());
    }
};

// NOLINTEND

} // namespace std
