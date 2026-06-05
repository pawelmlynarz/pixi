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
    PXFRONTEND_API ~Renderer() override;

    PXFRONTEND_API bool Initialize() override;
    PXFRONTEND_API void Shutdown() override;

    PXFRONTEND_API void Tick(float Dt) override;

    PXFRONTEND_API SharedPtr<RHIViewport> GetViewportResource(SharedRef<SWindow> Window) const override;

    PXFRONTEND_API void CreateViewport(SharedRef<SWindow> Window) override;

#if WITH_IMGUI
    PXFRONTEND_API class ImGuiRenderer& GetImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> Impl_{nullptr};
};

} // namespace px
