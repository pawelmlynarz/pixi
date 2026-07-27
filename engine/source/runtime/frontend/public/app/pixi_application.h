// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/misc.h"

#include <vector>

namespace px {

/**
 * The engine's single application instance. Owns the platform application, the renderer,
 * and the set of high-level windows shown to the user.
 */
class PixiApplication final : NonCopyableNonMovable {
  public:
    /**
     * Constructs the application around an already-created platform application.
     *
     * @param platformApplication The platform application that owns native windows and message dispatch.
     */
    PXENGINE_API explicit PixiApplication(SharedRef<class PlatformApplication> const& platformApplication);

    /**
     * Destroys the application.
     */
    PXENGINE_API ~PixiApplication();

    /**
     * Creates the application singleton, creating a default platform application for the current platform.
     *
     * @return Reference to the newly created application.
     */
    static PXENGINE_API PixiApplication& createApplication();

    /**
     * Creates the application singleton around the given platform application.
     *
     * @param platformApplication The platform application to use.
     *
     * @return Reference to the newly created application.
     */
    static PXENGINE_API PixiApplication& createApplication(SharedRef<PlatformApplication> const& platformApplication);

    /**
     * Shuts down and destroys the application singleton.
     */
    static PXENGINE_API void shutdownApplication();

    /**
     * @return True if the application singleton has been created.
     */
    static PXENGINE_API bool isInitialized();

    /**
     * Returns the current instance of the application. The application should have been initialized before
     * this method is called.
     *
     * @return Reference to the application.
     */
    static PXENGINE_API PixiApplication& get();

    /**
     * Initializes the renderer responsible for drawing all elements in this application.
     *
     * @param renderer The renderer to use.
     */
    PXENGINE_API bool initializeRenderer(SharedPtr<class Renderer> renderer);

    /**
     * Destroys the renderer.
     */
    PXENGINE_API void destroyRenderer();

    /**
     * Gets the renderer being used to draw this application.
     *
     * @return The renderer reference.
     */
    PXENGINE_API Renderer& getRenderer() const;

    /**
     * Ticks the application: polls platform messages, ticks the renderer, and draws all windows.
     *
     * @param dt Delta time, in seconds.
     */
    PXENGINE_API void tick(float dt);

    /**
     * Associates a high-level Window with a native window and ensures that it is tracked properly by the application.
     *
     * @param window A window to which to add a native window.
     * @param bShowImmediately True to show the window, false if you're going to call showWindow() yourself later.
     *
     * @return True if operation successful.
     */
    PXENGINE_API bool addWindow(SharedRef<class Window> window, bool bShowImmediately = true);

    /**
     * Finds the high-level Window associated with a given native platform window.
     *
     * @param platformWindow The native platform window to search for.
     *
     * @return The associated Window, or nullptr if none is tracked.
     */
    PXENGINE_API SharedPtr<Window> findWindowByPlatformWindow(SharedRef<class PlatformWindow> const& platformWindow);

  private:
    void drawWindows() const;

  private:
    SharedRef<PlatformApplication>  platformApplication_;
    SharedPtr<Renderer>             renderer_{nullptr};

    std::vector<SharedRef<Window>>  windows_;
};

} // namespace px
