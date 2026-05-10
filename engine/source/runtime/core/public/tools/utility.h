// © 2026 Pawel Mlynarz

#pragma once

#include "tools/asserts.h"

#include <utility>
#include <memory>

namespace px {

template <typename T>
using SharedPtr = std::shared_ptr<T>;

template<typename T>
class SharedRef {
public:
    SharedRef() = delete;

    SharedRef(SharedPtr<T> const& Ptr) noexcept
        : m_Ptr(Ptr)
    {
        PX_ASSERT_MSG(m_Ptr, "SharedRef constructed with null pointer");
    }

    SharedRef(SharedPtr<T>&& Ptr) noexcept
        : m_Ptr(std::move(Ptr))
    {
        PX_ASSERT_MSG(m_Ptr, "SharedRef constructed with null pointer");
    }

    SharedRef(SharedRef const&) = default;
    SharedRef& operator=(SharedRef const&) = default;

    SharedRef(SharedRef&&) noexcept = default;
    SharedRef& operator=(SharedRef&&) noexcept = default;
    
    T& operator*() const noexcept {
        return *m_Ptr;
    }

    T* operator->() const noexcept {
        return m_Ptr.get();
    }

    T* Get() const noexcept {
        return m_Ptr.get();
    }

    SharedPtr<T> ToShared() const noexcept {
        return m_Ptr;
    }

private:
   SharedPtr<T> m_Ptr;
};

} // namespace px
