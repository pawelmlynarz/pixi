// © 2026 Pawel Mlynarz

#pragma once

#include "rendercore_module.h"

// pxcore
#include "tools/utility.h"

namespace px {

class Window;

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
     * @param Window The window to fetch viewport from.
     *
     * @return RHIViewport associated with the Window provided.
     */
    virtual SharedPtr<struct RHIViewport> getViewportResource(SharedRef<Window> window) const = 0;

    /**
     * Creates a rendering viewport
     *
     * @param Window The window to create the viewport for.
     */
    virtual void createViewport(SharedRef<Window> window) = 0;
    virtual void requestResizeViewport(SharedRef<Window> window, uint16 sizeX, uint16 sizeY) = 0;
    /**
     * Gives the renderer a chance to wait for any render commands to be completed before returning.
     */
    virtual void flushCommands() const = 0;
};

} // namespace px
