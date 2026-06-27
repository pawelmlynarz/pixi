// © 2026 Pawel Mlynarz

#include "platform/generic_platform/generic_window_definition.h"
#include "platform/windows/windows_application.h"
#include "platform/windows/windows_window.h"

// GLFW
#include "core_globals.h"
#include "GLFW/glfw3.h"

#include <algorithm>

namespace px {

void WindowsApplication::initialize() {
}

void WindowsApplication::shutdown() {
    for (auto const& window : windows_) {
        window->destroyWindow();
    }
}

UniquePtr<PlatformWindow> WindowsApplication::createPlatformWindow() {
    return WindowsWindowFactory::create();
}

void WindowsApplication::initializeWindow(SharedRef<PlatformWindow> const& platformWindow, PlatformWindowDefinition const& windowDefinition) {
    SharedRef const windowsWindowRef{staticCastSharedRef<WindowsWindow>(platformWindow)};
    windowsWindowRef->initializeWindow(sharedThis(this).toPtr(), windowDefinition);

    windows_.emplace_back(windowsWindowRef);
}

void WindowsApplication::closeWindow(SharedRef<PlatformWindow> const& platformWindow) {
    auto foundWindow{std::ranges::find_if(
        windows_,
        [&platformWindow](auto const& w) {
            return w.get() == platformWindow.get();
        }
    )};

    pxAssert(foundWindow != windows_.end());
    (*foundWindow)->destroyWindow();
    windows_.erase(foundWindow);

    if (windows_.empty()) {
        requestEngineExit();
    }
}

void WindowsApplication::pollMessages() {
    glfwPollEvents();
}

UniquePtr<WindowsApplication> WindowsApplicationFactory::create() {
    return makeUnique<WindowsApplication>();
}

} // namespace px
