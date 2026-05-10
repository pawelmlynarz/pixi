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

    SharedPtr<T> ToShared() const noexcept {
        return Ptr_;
    }

  private:
    SharedPtr<T> Ptr_;
};

} // namespace px
