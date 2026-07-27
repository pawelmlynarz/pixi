// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/misc.h"

#include <vector>

namespace px {

class BaseRenderer;
class PlatformApplication;
class PlatformWindow;
class Window;

/**
 * The engine's single application instance. Owns the platform application, the renderer,
 * and the set of high-level windows shown to the user.
 */
class PixiApplication final : NonCopyableNonMovable {
  public:
    PXENGINE_API explicit PixiApplication(SharedRef<PlatformApplication> const& platformApplication);
    PXENGINE_API ~PixiApplication();

    static PXENGINE_API PixiApplication& createApplication();
    static PXENGINE_API PixiApplication& createApplication(SharedRef<PlatformApplication> const& platformApplication);
    static PXENGINE_API void shutdownApplication();
    static PXENGINE_API bool isInitialized();

    /**
     * Returns the current instance of the application. The application should have been initialized before
     * this method is called.
     *
     * @return Reference to the application.
     */
    static PixiApplication& get() {
        pxAssert(applicationInstance.get() != nullptr);
        return *applicationInstance;
    }

    /**
     * Initializes the renderer responsible for drawing all elements in this application.
     *
     * @param renderer The renderer to use.
     */
    PXENGINE_API bool initializeRenderer(SharedPtr<BaseRenderer> renderer);

    /**
     * Destroys the renderer.
     */
    PXENGINE_API void destroyRenderer();

    /**
     * Gets the renderer being used to draw this application.
     *
     * @return The renderer reference.
     */
    PXENGINE_API BaseRenderer& getRenderer() const;

    PXENGINE_API void tick(float dt);

    /**
     * Associates a high-level Window with a native window and ensures that it is tracked properly by the application.
     *
     * @param window A window to which to add a native window.
     * @param bShowImmediately True to show the window, false if you're going to call showWindow() yourself later.
     *
     * @return True if operation successful.
     */
    PXENGINE_API bool addWindow(SharedRef<Window> window, bool bShowImmediately = true);

    PXENGINE_API SharedPtr<Window> findWindowByPlatformWindow(SharedRef<PlatformWindow> const& platformWindow);

  private:
    void drawWindows() const;

  private:
    // Holds a pointer to the current application.
    static PXENGINE_API SharedPtr<PixiApplication> applicationInstance;

    SharedRef<PlatformApplication> platformApplication_;
    SharedPtr<BaseRenderer> renderer_{nullptr};

    std::vector<SharedRef<Window>> windows_;
};

} // namespace px
