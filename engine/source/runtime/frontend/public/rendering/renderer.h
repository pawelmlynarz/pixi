// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/misc.h"

namespace px {

class Window;

class Renderer final : NonCopyableNonMovable {
  public:
    PX_ENGINE_API Renderer();
    PX_ENGINE_API ~Renderer();

    /**
     * @brief Initializes the renderer.
     *
     * @return True if successful.
     */
    PX_ENGINE_API bool initialize();

    /**
     * @brief Shutdowns the renderer.
     */
    PX_ENGINE_API void shutdown();

    /**
     * @brief Ticks the renderer.
     *
     * @param dt Delta Time.
     */
    PX_ENGINE_API void tick(f32 dt);

    /**
     * @brief Retrieves the viewport RHI resource.
     *
     * @param window The window to fetch viewport from.
     *
     * @return RHIViewport associated with the window provided.
     */
    PX_ENGINE_API SharedPtr<struct RHIViewport> getViewportResource(SharedRef<Window> window) const;

    /**
     * Creates a rendering viewport
     *
     * @param window The window to create the viewport for.
     */
    PX_ENGINE_API void createViewport(SharedRef<Window> window);

    PX_ENGINE_API void requestResizeViewport(SharedRef<Window> window, u16 sizeX, u16 sizeY);

    /**
     * Gives the renderer a chance to wait for any render commands to be completed before returning.
     */
    PX_ENGINE_API void flushCommands() const;

#if WITH_IMGUI
    PX_ENGINE_API class ImGuiRenderer& getImGuiRenderer();
#endif

  private:
    struct Impl;
    UniquePtr<Impl> impl_{nullptr};
};

} // namespace px
