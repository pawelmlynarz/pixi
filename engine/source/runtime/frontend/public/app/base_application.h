// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "tools/misc.h"

namespace px {

class BaseRenderer;

/**
 * Base class for Pixi applications.
 */
class BaseApplication : NonCopyableNonMovable {
  public:
    PXENGINE_API BaseApplication() = default;
    PXENGINE_API virtual ~BaseApplication() = default;

    /**
     * Returns the current instance of the application. The application should have been initialized before
     * this method is called.
     *
     * @return Reference to the application.
     */
    static BaseApplication& get() {
        pxAssert(baseApplicationInstance.get() != nullptr);
        return *baseApplicationInstance;
    }

    /**
     * Initializes the renderer responsible for drawing all elements in this application.
     *
     * @param Renderer The renderer to use.
     */
    PXENGINE_API bool initializeRenderer(SharedPtr<BaseRenderer> renderer);

    /**
     * Destroys the renderer.
     */
    PXENGINE_API void destoryRenderer();

    /**
     * Gets the renderer being used to draw this application.
     *
     * @return The renderer reference.
     */
    PXENGINE_API BaseRenderer& getRenderer() const;

    /**
     * Associates a high-level Window with a native window and ensures that it is tracked properly by the application.
     *
     * @param Window A window to which to add a native window.
     * @param bShowImmediately True to show the window, false if you're going to call ShowWindow() yourself later.
     *
     * @return True if operation successful.
     */
    virtual bool addWindow(SharedRef<class Window> window, bool bShowImmediately = true) = 0;

  protected:
    // Holds a pointer to the current application.
    static PXENGINE_API SharedPtr<BaseApplication> baseApplicationInstance;

    // A pointer to the renderer used to render this application.
    SharedPtr<BaseRenderer> Renderer_{nullptr};
};

} // namespace px
