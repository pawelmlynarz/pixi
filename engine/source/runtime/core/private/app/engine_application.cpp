// © 2026 Pawel Mlynarz

#include "app/engine_application.h"
#include "app/platform_application.h"
#include "app/platform_application_misc.h"
#include "input/engine_input_system.h"
#include "window/generic_window.h"

namespace px {

namespace {

UniquePtr<EngineApplication> EngineApp;

} // namespace

void EngineRuntime::CreateApplication() {
    CreateApplication(SharedRef<PlatformApplication>(PlatformApplicationMisc::CreateApplication()));
}

void EngineRuntime::CreateApplication(SharedRef<PlatformApplication> const PlatformApplication) {
    EngineApp = MakeUnique<EngineApplication>(PlatformApplication);
}

void EngineRuntime::Shutdown() {
    EngineApp.reset();
}

EngineApplication::EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication)
    : PlatformApplication_(InPlatformApplication) {
    PlatformApplication_->Initialize();
    PlatformApplication_->SetMessageHandler(SharedRef<IGenericApplicationMessageHandler>(MakeShared<EngineInputSystem>(PlatformApplication_)));
}

EngineApplication::~EngineApplication() {
    PlatformApplication_->Shutdown();
}

void EngineApplication::Tick() {
    PlatformApplication_->PollMessages();
}

bool EngineRuntime::IsInitialized() {
    return EngineApp != nullptr;
}

EngineApplication& EngineRuntime::GetApplication() {
    PX_ASSERT(IsInitialized());
    return *EngineApp;
}

bool EngineApplication::AddWindow(GenericWindowDefinition const& WindowDefinition, bool const bShowImmediately) const {
    SharedRef<GenericWindow> const Window{PlatformApplication_->CreatePlatformWindow()};
    PlatformApplication_->InitializeWindow(Window, WindowDefinition);
    if (bShowImmediately)
        Window->Show();
    return true;
}

} // namespace px
