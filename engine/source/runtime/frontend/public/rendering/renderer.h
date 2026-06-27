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

    PXFRONTEND_API bool initialize() override;
    PXFRONTEND_API void shutdown() override;

    PXFRONTEND_API void tick(float dt) override;

    PXFRONTEND_API SharedPtr<RHIViewport> getViewportResource(SharedRef<SWindow> window) const override;

    PXFRONTEND_API void createViewport(SharedRef<SWindow> window) override;

#if WITH_IMGUI
    PXFRONTEND_API class ImGuiRenderer& getImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> impl_{nullptr};
};

} // namespace px
