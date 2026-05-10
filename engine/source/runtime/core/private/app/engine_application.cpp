// © 2026 Pawel Mlynarz

#include "app/engine_application.h"
#include "app/platform_application.h"
#include "app/platform_application_misc.h"
#include "window/generic_window.h"

namespace px {

namespace {

UniquePtr<EngineApplication> EngineApp;

} // namespace

void EngineApplication::Create() {
    Create(SharedRef<PlatformApplication>(PlatformApplicationMisc::CreateApplication()));
}

void EngineApplication::Create(SharedRef<PlatformApplication> const PlatformApplication) {
    EngineApp = MakeUnique<EngineApplication>(PlatformApplication);
}

void EngineApplication::Shutdown() {
    EngineApp.reset();
}

bool EngineApplication::IsInitialized() {
    return EngineApp != nullptr;
}

EngineApplication& EngineApplication::Get() {
    PX_ASSERT(IsInitialized());
    return *EngineApp;
}

EngineApplication::EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication)
    : PlatformApplication_(InPlatformApplication) {
}

bool EngineApplication::AddWindow(GenericWindowDefinition const& WindowDefinition, bool const bShowImmediately) {
    SharedRef<GenericWindow> const Window{PlatformApplication_->CreatePlatformWindow()};
    PlatformApplication_->InitializeWindow(Window, WindowDefinition);
    if (bShowImmediately)
        Window->Show();
    return true;
}

} // namespace px
