// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"

// pxcore
#include "tools/misc.h"
#include "tools/utility.h"

namespace px {

class BaseRenderer;

/**
 * Base class for Pixi applications.
 */
class BaseApplication : NonCopyableNonMovable {
  public:
    PXFRONTEND_API BaseApplication() = default;
    PXFRONTEND_API virtual ~BaseApplication() = default;

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
    PXFRONTEND_API bool initializeRenderer(SharedPtr<BaseRenderer> renderer);

    /**
     * Destroys the renderer.
     */
    PXFRONTEND_API void destoryRenderer();

    /**
     * Gets the renderer being used to draw this application.
     *
     * @return The renderer reference.
     */
    PXFRONTEND_API BaseRenderer& getRenderer() const;

    /**
     * Associates a high-level Window with a native window and ensures that it is tracked properly by the application.
     *
     * @param SWindow A window to which to add a native window.
     * @param bShowImmediately True to show the window, false if you're going to call ShowWindow() yourself later.
     *
     * @return True if operation successful.
     */
    virtual bool addWindow(SharedRef<class SWindow> window, bool bShowImmediately = true) = 0;

  protected:
    // Holds a pointer to the current application.
    static PXFRONTEND_API SharedPtr<BaseApplication> baseApplicationInstance;

    // A pointer to the renderer used to render this application.
    SharedPtr<BaseRenderer> Renderer_{nullptr};
};

} // namespace px
