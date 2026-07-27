// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/misc.h"

namespace px {

class Window;

class Renderer final : NonCopyableNonMovable {
  public:
    PXENGINE_API Renderer();
    PXENGINE_API ~Renderer();

    /**
     * @brief Initializes the renderer.
     *
     * @return True if successful.
     */
    PXENGINE_API bool initialize();

    /**
     * @brief Shutdowns the renderer.
     */
    PXENGINE_API void shutdown();

    /**
     * @brief Ticks the renderer.
     *
     * @param dt Delta Time.
     */
    PXENGINE_API void tick(float dt);

    /**
     * @brief Retrieves the viewport RHI resource.
     *
     * @param window The window to fetch viewport from.
     *
     * @return RHIViewport associated with the window provided.
     */
    PXENGINE_API SharedPtr<struct RHIViewport> getViewportResource(SharedRef<Window> window) const;

    /**
     * Creates a rendering viewport
     *
     * @param window The window to create the viewport for.
     */
    PXENGINE_API void createViewport(SharedRef<Window> window);

    PXENGINE_API void requestResizeViewport(SharedRef<Window> window, uint16 sizeX, uint16 sizeY);

    /**
     * Gives the renderer a chance to wait for any render commands to be completed before returning.
     */
    PXENGINE_API void flushCommands() const;

#if WITH_IMGUI
    PXENGINE_API class ImGuiRenderer& getImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> impl_{nullptr};
};

} // namespace px
