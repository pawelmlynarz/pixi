// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/misc.h"
#include "generic_window_definition.h"
#include "tools/utility.h"

namespace px {

struct GenericOSWindowHandle {
    void* Handle{nullptr};

    constexpr bool IsValid() const noexcept { return Handle != nullptr; }

    template <typename T>
    T* As() const { return static_cast<T*>(Handle); }
};

class PlatformApplication;

class GenericWindow : NonCopyableNonMovable, public EnableSharedFromThis<GenericWindow> {
  public:
    virtual ~GenericWindow() = default;

  public:
    virtual void InitializeWindow(SharedPtr<PlatformApplication> const OwningApplication, GenericWindowDefinition const& WindowDefinition);
    virtual void DestroyWindow() {}

    virtual SharedRef<PlatformApplication> GetOwningApplication() const { return OwningApplication_; }

    virtual GenericOSWindowHandle GetOSWindowHandle() const { return GenericOSWindowHandle(nullptr); }

    PXCORE_API virtual void Show() {}
    PXCORE_API virtual void Hide() {}
    PXCORE_API virtual bool IsVisible() const { return false; }

  protected:
    SharedPtr<PlatformApplication> OwningApplication_{nullptr};
    GenericWindowDefinition Definition_;
};

} // namespace px
