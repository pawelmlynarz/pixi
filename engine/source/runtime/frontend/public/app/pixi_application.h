// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"
#include "app/base_application.h"

// pxcore
#include "tools/utility.h"

#include <vector>

namespace px {

class PlatformApplication;
class BaseRenderer;

class SimpleApplication final : public BaseApplication {
  public:
    SimpleApplication(SharedRef<PlatformApplication> const& PlatformApplication);
    ~SimpleApplication() override;

    static PXFRONTEND_API SimpleApplication& CreateApplication();
    static PXFRONTEND_API SimpleApplication& CreateApplication(SharedRef<class PlatformApplication> const& InPlatformApplication);
    static PXFRONTEND_API void ShutdownApplication();
    static PXFRONTEND_API bool IsInitialized();

    static SimpleApplication& Get() {
        Assert(ApplicationInstance_.get() != nullptr);
        return *ApplicationInstance_;
    }

    PXFRONTEND_API void Tick(float Dt);
    PXFRONTEND_API bool AddWindow(SharedRef<SWindow> SWindow, bool bShowImmediately) override;

  private:
    void DrawWindows() const;

  private:
    // Holds a pointer to the current application.
    static PXFRONTEND_API SharedPtr<SimpleApplication> ApplicationInstance_;

    SharedRef<PlatformApplication> PlatformApplication_;

    std::vector<SharedRef<SWindow>> Windows_;
};

} // namespace px
