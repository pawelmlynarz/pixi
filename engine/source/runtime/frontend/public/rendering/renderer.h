// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"

// pxrendercore
#include "base_renderer.h"

// pxcore
#include "tools/utility.h"

namespace px {

class SWindow;

class Renderer final : public BaseRenderer {
  public:
    PXFRONTEND_API Renderer();
    PXFRONTEND_API virtual ~Renderer() override;

    PXFRONTEND_API virtual bool Initialize() override;
    PXFRONTEND_API virtual void Shutdown() override;

    PXFRONTEND_API virtual void Tick(float const Dt) override;

    PXFRONTEND_API virtual SharedPtr<RHIViewport> GetViewportResource(SharedRef<SWindow> Window) const override;

    PXFRONTEND_API virtual void CreateViewport(SharedRef<SWindow> Window) override;

#if WITH_IMGUI
    PXFRONTEND_API class ImGuiRenderer& GetImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> Impl_{nullptr};
};

} // namespace px
