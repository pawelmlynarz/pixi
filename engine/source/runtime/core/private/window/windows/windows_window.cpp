// © 2026 Pawel Mlynarz

#include "window/windows/windows_window.h"

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

} // namespace

void WindowsWindow::InitializeWindow(GenericWindowDefinition const& WindowDefiinition) {
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
}

void WindowsWindow::DestoryWindow() {
    if (!Handle_)
        return;

    glfwDestroyWindow(Handle_);
    Handle_ = nullptr;
    Hwnd_ = nullptr;
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
