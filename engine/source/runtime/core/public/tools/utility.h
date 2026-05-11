// © 2026 Pawel Mlynarz

#pragma once

#include "tools/asserts.h"

#include <utility>
#include <memory>

namespace px {

template <typename T>
using UniquePtr = std::unique_ptr<T>;

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

template <typename T>
class SharedRef {
  public:
    SharedRef() = delete;

    SharedRef(SharedPtr<T> const& Ptr) noexcept
        : Ptr_(Ptr) {
        PX_ASSERT_MSG(Ptr_, "SharedRef constructed with null pointer");
    }

    SharedRef(SharedPtr<T>&& Ptr) noexcept
        : Ptr_(std::move(Ptr)) {
        PX_ASSERT_MSG(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U> const& Ptr) noexcept
        : Ptr_(Ptr) {
        PX_ASSERT_MSG(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedPtr<U>&& Ptr) noexcept
        : Ptr_(std::move(Ptr)) {
        PX_ASSERT_MSG(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef(SharedRef<U> const& Other) noexcept
        : Ptr_(Other.ToPtr()) {
        PX_ASSERT_MSG(Ptr_, "SharedRef constructed with null pointer");
    }

    template <typename U>
        requires std::convertible_to<U*, T*>
    SharedRef& operator=(SharedRef<U> const& Other) noexcept {
        Ptr_ = Other.ToPtr();
        PX_ASSERT_MSG(Ptr_, "SharedRef assigned null pointer");
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

  private:
    SharedPtr<T> Ptr_;
};

template <typename TTo, typename TFrom>
[[nodiscard]] SharedPtr<TTo> StaticCastSharedPtr(SharedPtr<TFrom> const& Ptr) noexcept {
    return std::static_pointer_cast<TTo>(Ptr);
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> StaticCastSharedRef(SharedPtr<TFrom> const& Ptr) noexcept {
    return SharedRef<TTo>(std::static_pointer_cast<TTo>(Ptr));
}

template <typename TTo, typename TFrom>
[[nodiscard]] SharedRef<TTo> StaticCastSharedRef(SharedRef<TFrom> const& Ref) noexcept {
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

} // namespace px
