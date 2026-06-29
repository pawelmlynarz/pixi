// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "app/base_application.h"

#include <vector>

namespace px {

class PlatformApplication;
class BaseRenderer;

class SimpleApplication final : public BaseApplication {
  public:
    SimpleApplication(SharedRef<PlatformApplication> const& platformApplication);
    ~SimpleApplication() override;

    static PXENGINE_API SimpleApplication& createApplication();
    static PXENGINE_API SimpleApplication& createApplication(SharedRef<class PlatformApplication> const& inPlatformApplication);
    static PXENGINE_API void shutdownApplication();
    static PXENGINE_API bool isInitialized();

    static SimpleApplication& get() {
        pxAssert(applicationInstance.get() != nullptr);
        return *applicationInstance;
    }
    
    PXENGINE_API void tick(float dt);
    PXENGINE_API bool addWindow(SharedRef<Window> window, bool bShowImmediately) override;

    PXENGINE_API SharedPtr<Window> findWindowByPlatformWindow(SharedRef<class PlatformWindow> const& platformWindow);

  private:
    void drawWindows() const;

  private:
    // Holds a pointer to the current application.
    static PXENGINE_API SharedPtr<SimpleApplication> applicationInstance;

    SharedRef<PlatformApplication> platformApplication_;

    std::vector<SharedRef<Window>> windows_;
};

} // namespace px
