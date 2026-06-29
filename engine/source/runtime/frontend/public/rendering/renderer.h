// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// pxrendercore
#include "base_renderer.h"

// pxcore
#include "tools/utility.h"

namespace px {

class SWindow;

class Renderer final : public BaseRenderer {
  public:
    PXENGINE_API Renderer();
    PXENGINE_API ~Renderer() override;

    PXENGINE_API bool initialize() override;
    PXENGINE_API void shutdown() override;

    PXENGINE_API void tick(float dt) override;

    PXENGINE_API SharedPtr<RHIViewport> getViewportResource(SharedRef<SWindow> window) const override;

    PXENGINE_API void createViewport(SharedRef<SWindow> window) override;

    PXENGINE_API void requestResizeViewport(SharedRef<SWindow> window, uint16 sizeX, uint16 sizeY) override;

    PXENGINE_API void flushCommands() const override;

#if WITH_IMGUI
    PXENGINE_API class ImGuiRenderer& getImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> impl_{nullptr};
};

} // namespace px
