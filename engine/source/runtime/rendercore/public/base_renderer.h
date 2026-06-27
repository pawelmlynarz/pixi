// © 2026 Pawel Mlynarz

#pragma once

#include "rendercore_module.h"

// pxcore
#include "tools/utility.h"

namespace px {

class SWindow;

class BaseRenderer {
  public:
    BaseRenderer() = default;
    virtual ~BaseRenderer() = default;

    /**
     * @brief Initializes the renderer.
     *
     * @return True if successful.
     */
    virtual bool initialize() = 0;

    /**
     * @brief Shutdowns the renderer.
     */
    virtual void shutdown() = 0;

    /**
     * @brief Ticks the renderer.
     *
     * @param Dt Delta Time.
     */
    virtual void tick(float dt) = 0;

    /**
     * @brief Retrieves the viewport RHI resource.
     *
     * @param SWindow The window to fetch viewport from.
     *
     * @return RHIViewport associated with the SWindow provided.
     */
    virtual SharedPtr<struct RHIViewport> getViewportResource(SharedRef<SWindow> window) const = 0;

    /**
     * Creates a rendering viewport
     *
     * @param SWindow The window to create the viewport for.
     */
    virtual void createViewport(SharedRef<SWindow> window) = 0;
};

} // namespace px
