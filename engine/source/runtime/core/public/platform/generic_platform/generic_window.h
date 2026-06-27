// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "tools/misc.h"
#include "generic_window_definition.h"
#include "tools/utility.h"

namespace px {

struct GenericOSWindowHandle {
    void* Handle{nullptr};

    constexpr bool isValid() const noexcept { return Handle != nullptr; }

    template <typename T>
    T* as() const { return static_cast<T*>(Handle); }
};

class PlatformApplication;

class GenericWindow : NonCopyableNonMovable, public EnableSharedFromThis<GenericWindow> {
  public:
    virtual ~GenericWindow() = default;

  public:
    virtual void initializeWindow(SharedPtr<PlatformApplication> owningApplication, GenericWindowDefinition const& windowDefinition);
    virtual void destroyWindow() {}

    virtual SharedRef<PlatformApplication> getOwningApplication() const { return OwningApplication_; }

    virtual GenericOSWindowHandle getOsWindowHandle() const { return GenericOSWindowHandle(nullptr); }

    PXCORE_API virtual void show() {}
    PXCORE_API virtual void hide() {}
    PXCORE_API virtual bool isVisible() const { return false; }

  protected:
    SharedPtr<PlatformApplication> OwningApplication_{nullptr};
    GenericWindowDefinition Definition_;
};

} // namespace px
