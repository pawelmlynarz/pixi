// © 2026 Pawel Mlynarz

#pragma once

#include "ui_module.h"
#include "app/base_application.h"

// pxcore
#include "tools/utility.h"

#include <vector>

namespace px {

class PlatformApplication;
class BaseRenderer;

class SimpleApplication final : public BaseApplication {
  public:
    SimpleApplication(SharedRef<PlatformApplication> const PlatformApplication);
    ~SimpleApplication();

    static PXUI_API SimpleApplication& CreateApplication();
    static PXUI_API SimpleApplication& CreateApplication(SharedRef<class PlatformApplication> const InPlatformApplication);
    static PXUI_API void ShutdownApplication();
    static PXUI_API bool IsInitialized();

    static SimpleApplication& Get() {
        Assert(ApplicationInstance_.get() != nullptr);
        return *ApplicationInstance_;
    }

    PXUI_API void Tick();
    PXUI_API virtual bool AddWindow(SharedRef<SWindow> SWindow, bool const bShowImmediately) override;

  private:
    void DrawWindows() const;

  private:
    // Holds a pointer to the current application.
    static PXUI_API SharedPtr<SimpleApplication> ApplicationInstance_;

    SharedRef<PlatformApplication> PlatformApplication_;
    SharedPtr<BaseRenderer> Renderer_{nullptr};

    std::vector<SharedRef<SWindow>> Windows_;
};

} // namespace px
