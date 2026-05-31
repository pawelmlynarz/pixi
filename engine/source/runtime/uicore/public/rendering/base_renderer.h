// © 2026 Pawel Mlynarz

#pragma once

#include "uicore_module.h"

// pxcore
#include "tools/utility.h"

namespace px {

class BaseRenderer {
  public:
    PXUICORE_API BaseRenderer() = default;
    virtual ~BaseRenderer() = default;

    /**
     * @brief Initializes the renderer.
     *
     * @return True if successful.
     */
    virtual bool Initialize() = 0;

    /**
     * @brief Shutdowns the renderer.
     */
    virtual void Shutdown() = 0;

    /**
     * @brief Retrieves the viewport RHI resource.
     *
     * @param SWindow The window to fetch viewport from.
     *
     * @return RHIViewport associated with the SWindow provided.
     */
    virtual SharedPtr<struct RHIViewport> GetViewportResource(SharedRef<class SWindow> SWindow) const = 0;

    /**
     * Creates a rendering viewport
     *
     * @param SWindow The window to create the viewport for.
     */
    virtual void CreateViewport(SharedRef<class SWindow> const SWindow) = 0;
};

} // namespace px
