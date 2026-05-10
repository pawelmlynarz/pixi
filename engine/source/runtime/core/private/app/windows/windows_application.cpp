// © 2026 Pawel Mlynarz

#include "app/windows/windows_application.h"
#include "window/windows/windows_window.h"

namespace px {

UniquePtr<GenericWindow> WindowsApplication::CreatePlatformWindow() {
    return WindowsWindowFactory::Create();
}

void WindowsApplication::InitializeWindow(SharedRef<GenericWindow> const& Window, GenericWindowDefinition const& WindowDefiinition) {
    SharedRef const WindowsWindowRef{StaticCastSharedRef<WindowsWindow>(Window)};
    WindowsWindowRef->InitializeWindow(WindowDefiinition);

    Windows_.emplace_back(WindowsWindowRef);
}

UniquePtr<WindowsApplication> WindowsApplicationFactory::Create() {
    return MakeUnique<WindowsApplication>();
}

} // namespace px
