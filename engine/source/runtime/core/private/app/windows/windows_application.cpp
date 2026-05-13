// © 2026 Pawel Mlynarz

#include <algorithm>

#include "app/windows/windows_application.h"
#include "window/windows/windows_window.h"

// GLFW
#include "core_misc.h"
#include "GLFW/glfw3.h"

namespace px {

void WindowsApplication::Initialize() {
}

void WindowsApplication::Shutdown() {
    for (auto const& Window : Windows_) {
        Window->DestroyWindow();
    }
}

UniquePtr<GenericWindow> WindowsApplication::CreatePlatformWindow() {
    return WindowsWindowFactory::Create();
}

void WindowsApplication::InitializeWindow(SharedRef<GenericWindow> const& Window, GenericWindowDefinition const& WindowDefinition) {
    SharedRef const WindowsWindowRef{StaticCastSharedRef<WindowsWindow>(Window)};
    WindowsWindowRef->InitializeWindow(SharedThis(this).ToPtr(), WindowDefinition);

    Windows_.emplace_back(WindowsWindowRef);
}

void WindowsApplication::CloseWindow(SharedRef<GenericWindow> const& Window) {
    auto FoundWindow{std::ranges::find_if(
        Windows_,
        [&Window](auto const& W) {
            return W.Get() == Window.Get();
        })};

    PX_ASSERT(FoundWindow != Windows_.end());
    (*FoundWindow)->DestroyWindow();
    Windows_.erase(FoundWindow);

    if (Windows_.empty())
        RequestEngineExit();
}

void WindowsApplication::PollMessages() {
    glfwPollEvents();
}

UniquePtr<WindowsApplication> WindowsApplicationFactory::Create() {
    return MakeUnique<WindowsApplication>();
}

} // namespace px
