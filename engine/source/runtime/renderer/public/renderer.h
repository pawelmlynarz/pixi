// © 2026 Pawel Mlynarz

#pragma once

#include "renderer_module.h"

// pxuicore
#include "rendering/base_renderer.h"

// pxcore
#include "tools/utility.h"

#include <unordered_map>

namespace px {

class SWindow;

class Renderer final : public BaseRenderer {
  public:
    PXRENDERER_API Renderer();
    PXRENDERER_API virtual ~Renderer() override;

    PXRENDERER_API virtual bool Initialize() override;
    PXRENDERER_API virtual void Shutdown() override;

    PXRENDERER_API virtual SharedPtr<RHIViewport> GetViewportResource(SharedRef<SWindow> Window) const override;

    PXRENDERER_API virtual void CreateViewport(SharedRef<SWindow> Window) override;

  private:
    struct Impl;
    UniquePtr<Impl> Impl_{nullptr};
};

} // namespace px
