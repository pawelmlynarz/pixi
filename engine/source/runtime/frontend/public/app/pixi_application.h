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
    SimpleApplication(SharedRef<PlatformApplication> const& platformApplication);
    ~SimpleApplication() override;

    static PXFRONTEND_API SimpleApplication& createApplication();
    static PXFRONTEND_API SimpleApplication& createApplication(SharedRef<class PlatformApplication> const& inPlatformApplication);
    static PXFRONTEND_API void shutdownApplication();
    static PXFRONTEND_API bool isInitialized();

    static SimpleApplication& get() {
        pxAssert(applicationInstance.get() != nullptr);
        return *applicationInstance;
    }

    PXFRONTEND_API void tick(float dt);
    PXFRONTEND_API bool addWindow(SharedRef<Window> window, bool bShowImmediately) override;

    PXFRONTEND_API SharedPtr<Window> findWindowByPlatformWindow(SharedRef<class PlatformWindow> const& platformWindow);

  private:
    void drawWindows() const;

  private:
    // Holds a pointer to the current application.
    static PXFRONTEND_API SharedPtr<SimpleApplication> applicationInstance;

    SharedRef<PlatformApplication> platformApplication_;

    std::vector<SharedRef<Window>> windows_;
};

} // namespace px
