// © 2026 Pawel Mlynarz

#pragma once

#include "core.h"
#include "tools/misc.h"
#include "generic_window_definition.h"
#include "app/platform_application.h"
#include "tools/utility.h"

namespace px {

class GenericWindow : NonCopyableNonMovable, public EnableSharedFromThis<GenericWindow> {
  public:
    virtual ~GenericWindow() = default;

  public:
    virtual void InitializeWindow([[maybe_unused]] SharedPtr<class PlatformApplication> OwningApplication,
                                  [[maybe_unused]] GenericWindowDefinition const& WindowDefiinition) {}
    virtual void DestoryWindow() {}

    virtual SharedRef<PlatformApplication> GetOwningApplication() const {
        static SharedRef<PlatformApplication> NullApplication{MakeShared<PlatformApplication>()};
        return NullApplication;
    }

    [[nodiscard]]
    virtual void* GetOSWindowHandle() const { return nullptr; }

    PXCORE_API virtual void Show() {}
    PXCORE_API virtual void Hide() {}
    PXCORE_API virtual bool IsVisible() const { return false; }
};

} // namespace px
