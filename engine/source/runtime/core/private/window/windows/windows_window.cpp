// © 2026 Pawel Mlynarz

#include "window/windows/windows_window.h"
#include "app/windows/windows_application.h"

// GLFW
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

namespace px {

namespace {

bool bGLFWInitialized{false};

void GLFWErrorCallback([[maybe_unused]] int const ErrorCode, [[maybe_unused]] char const* const Description) {
    PX_TODO("Handle error and implement logger.");
}

void EnsureGLFWInitialized() {
    if (bGLFWInitialized)
        return;

    glfwSetErrorCallback(GLFWErrorCallback);
    PX_ASSERT(glfwInit());

    bGLFWInitialized = true;
}

void GLFWKeyCallback(GLFWwindow* const Window, int32_t const Key, int32_t const Scancode, int32_t const Action, int32_t const Mods) {
    WindowsWindow* const WinWindow{reinterpret_cast<WindowsWindow*>(glfwGetWindowUserPointer(Window))};
    SharedRef const MessageHandler{WinWindow->GetOwningApplication()->GetMessageHandler()};

    switch (uint32 const CharacterCode{static_cast<uint32>(Scancode)}; Action) {
    case GLFW_PRESS:
        MessageHandler->OnKeyDown(Key, CharacterCode, false);
        break;

    case GLFW_REPEAT:
        MessageHandler->OnKeyDown(Key, CharacterCode, true);
        break;

    case GLFW_RELEASE:
        MessageHandler->OnKeyUp(Key, CharacterCode, false);
        break;

    default: break;
    }
}

void GLFWCharCallback(GLFWwindow* const Window, uint32_t const Codepoint) {
}

void GLFWButtonCallback(GLFWwindow* const Window, int32_t const Button, int32_t const Action, int32_t const Mods) {
}

void GLFWCursorPosCallback(GLFWwindow* Window, double const X, double const Y) {
}

void GLFWScrollCallback(GLFWwindow* const Window, double const XOffset, double const YOffset) {
}

void GLFWCloseCallback(GLFWwindow* const Window) {
    WindowsWindow* const WinWindow{reinterpret_cast<WindowsWindow*>(glfwGetWindowUserPointer(Window))};
    SharedRef const MessageHandler{WinWindow->GetOwningApplication()->GetMessageHandler()};
    MessageHandler->OnWindowClose(SharedThis(WinWindow));
}

} // namespace

void WindowsWindow::InitializeWindow(SharedPtr<PlatformApplication> OwningApplication, GenericWindowDefinition const& WindowDefiinition) {
    OwningApplication_ = StaticCastSharedPtr<WindowsApplication>(OwningApplication);

    EnsureGLFWInitialized();

    Definition_ = WindowDefiinition;

    glfwDefaultWindowHints();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_VISIBLE, 0);
    glfwWindowHint(GLFW_DECORATED, Definition_.bDecorated ? 1 : 0);
    glfwWindowHint(GLFW_RESIZABLE, Definition_.bResizable ? 1 : 0);

    Handle_ = glfwCreateWindow(Definition_.WidthDesired, Definition_.HeightDesired, "Window", nullptr, nullptr);
    if (!Handle_) {
        glfwTerminate();
        PX_ASSERT(false);
    }

    Hwnd_ = glfwGetWin32Window(Handle_);

    glfwSetWindowUserPointer(Handle_, this);
    glfwSetKeyCallback(Handle_, GLFWKeyCallback);
    glfwSetCharCallback(Handle_, GLFWCharCallback);
    glfwSetMouseButtonCallback(Handle_, GLFWButtonCallback);
    glfwSetCursorPosCallback(Handle_, GLFWCursorPosCallback);
    glfwSetScrollCallback(Handle_, GLFWScrollCallback);
    glfwSetWindowCloseCallback(Handle_, GLFWCloseCallback);
}

void WindowsWindow::DestoryWindow() {
    if (!Handle_)
        return;

    glfwDestroyWindow(Handle_);
    Handle_ = nullptr;
    Hwnd_ = nullptr;
}

SharedRef<PlatformApplication> WindowsWindow::GetOwningApplication() const {
    PX_ASSERT(OwningApplication_);
    return SharedRef(OwningApplication_);
}

void* WindowsWindow::GetOSWindowHandle() const {
    return Handle_;
}

void WindowsWindow::Show() {
    PX_ASSERT(Handle_ != nullptr);
    glfwShowWindow(Handle_);
}

void WindowsWindow::Hide() {
    PX_ASSERT(Handle_ != nullptr);
    glfwHideWindow(Handle_);
}

bool WindowsWindow::IsVisible() const {
    if (!Handle_)
        return false;
    return glfwGetWindowAttrib(Handle_, GLFW_VISIBLE) == GLFW_TRUE;
}

UniquePtr<WindowsWindow> WindowsWindowFactory::Create() {
    return MakeUnique<WindowsWindow>();
}

} // namespace px
