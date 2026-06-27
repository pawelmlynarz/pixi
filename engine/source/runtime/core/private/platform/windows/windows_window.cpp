// © 2026 Pawel Mlynarz

#include "platform/windows/windows_window.h"
#include "platform/windows/windows_application.h"

// GLFW
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace px {

namespace {

bool bGLFWInitialized{false};

void glfwErrorCallback([[maybe_unused]] int const errorCode, [[maybe_unused]] char const* const description) {
    pxToDo("Handle error and implement logger.");
}

void ensureGlfwInitialized() {
    if (bGLFWInitialized) {
        return;
    }

    glfwSetErrorCallback(glfwErrorCallback);
    pxAssert(glfwInit());

    bGLFWInitialized = true;
}

void glfwKeyCallback(GLFWwindow* const window, int32_t const key, int32_t const scancode, int32_t const action, [[maybe_unused]] int32_t const mods) {
    WindowsWindow const* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};

    switch (uint32 const characterCode{static_cast<uint32>(scancode)}; action) {
    case GLFW_PRESS:
        messageHandler->onKeyDown(key, characterCode, false);
        break;

    case GLFW_REPEAT:
        messageHandler->onKeyDown(key, characterCode, true);
        break;

    case GLFW_RELEASE:
        messageHandler->onKeyUp(key, characterCode, false);
        break;

    default: break;
    }
}

void glfwCharCallback(GLFWwindow* const window, uint32_t const codepoint) {
    WindowsWindow const* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};

    messageHandler->onKeyChar(codepoint, false);
}

void glfwMouseButtonCallback(GLFWwindow* const window, int32_t const button, int32_t const action, [[maybe_unused]] int32_t const mods) {
    WindowsWindow* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};

    EMouseButton buttonEnum{EMouseButton::Left};

    switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
        buttonEnum = EMouseButton::Left;
        break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
        buttonEnum = EMouseButton::Middle;
        break;

    case GLFW_MOUSE_BUTTON_RIGHT:
        buttonEnum = EMouseButton::Right;
        break;

    default: break;
    }

    double mouseX{};
    double mouseY{};
    glfwGetCursorPos(window, &mouseX, &mouseY);
    Vector2 const mousePos{static_cast<float>(mouseX), static_cast<float>(mouseY)};

    if (action == GLFW_PRESS) {
        messageHandler->onMouseDown(sharedThis(winWindow), buttonEnum, mousePos);
    } else if (action == GLFW_RELEASE) {
        messageHandler->onMouseUp(sharedThis(winWindow), buttonEnum, mousePos);
    }
}

void glfwCursorPosCallback(GLFWwindow* window, double const x, double const y) {
    WindowsWindow* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};

    messageHandler->onMouseMoved(sharedThis(winWindow), {x, y});
}

void glfwScrollCallback(GLFWwindow* const window, double const xOffset, double const yOffset) {
}

void glfwCloseCallback(GLFWwindow* const window) {
    WindowsWindow* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};
    messageHandler->onWindowClose(sharedThis(winWindow));
}

void glfwFramebufferResizeCallback(GLFWwindow* const window, int const width, int const height) {
    WindowsWindow* const winWindow{static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window))};
    SharedRef const messageHandler{winWindow->getOwningApplication()->getMessageHandler()};
    messageHandler->onWindowResized(sharedThis(winWindow), static_cast<uint16>(width), static_cast<uint16>(height), false);
}

} // namespace

void WindowsWindow::initializeWindow(SharedPtr<PlatformApplication> owningApplication, PlatformWindowDefinition const& windowDefinition) {
    PlatformWindow::initializeWindow(owningApplication, windowDefinition);

    ensureGlfwInitialized();

    Definition_ = windowDefinition;

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, 0);
    glfwWindowHint(GLFW_DECORATED, Definition_.decorated ? 1 : 0);
    glfwWindowHint(GLFW_RESIZABLE, Definition_.resizable ? 1 : 0);

    handle_ = glfwCreateWindow(Definition_.widthDesired, Definition_.heightDesired, "Window", nullptr, nullptr);
    if (!handle_) {
        glfwTerminate();
        pxAssert(false);
    }

    hwnd_ = glfwGetWin32Window(handle_);

    glfwSetWindowUserPointer(handle_, this);
    glfwSetKeyCallback(handle_, glfwKeyCallback);
    glfwSetCharCallback(handle_, glfwCharCallback);
    glfwSetMouseButtonCallback(handle_, glfwMouseButtonCallback);
    glfwSetCursorPosCallback(handle_, glfwCursorPosCallback);
    glfwSetScrollCallback(handle_, glfwScrollCallback);
    glfwSetWindowCloseCallback(handle_, glfwCloseCallback);
    glfwSetFramebufferSizeCallback(handle_, glfwFramebufferResizeCallback);
}

void WindowsWindow::destroyWindow() {
    if (!handle_) {
        return;
    }

    glfwDestroyWindow(handle_);
    handle_ = nullptr;
    hwnd_ = nullptr;
}

SharedRef<PlatformApplication> WindowsWindow::getOwningApplication() const {
    pxAssert(OwningApplication_);
    return OwningApplication_;
}

GenericOSWindowHandle WindowsWindow::getOsWindowHandle() const {
    return {static_cast<void*>(hwnd_)};
}

void WindowsWindow::show() {
    pxAssert(handle_ != nullptr);
    glfwShowWindow(handle_);
}

void WindowsWindow::hide() {
    pxAssert(handle_ != nullptr);
    glfwHideWindow(handle_);
}

bool WindowsWindow::isVisible() const {
    if (!handle_) {
        return false;
    }
    return glfwGetWindowAttrib(handle_, GLFW_VISIBLE) == GLFW_TRUE;
}

bool WindowsWindow::isFullscreenSupported() const {
    return glfwGetPrimaryMonitor() != nullptr;
}

UniquePtr<WindowsWindow> WindowsWindowFactory::create() {
    return makeUnique<WindowsWindow>();
}

} // namespace px
