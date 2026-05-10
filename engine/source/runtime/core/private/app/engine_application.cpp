// © 2026 Pawel Mlynarz

#include "app/engine_application.h"

#include "app/platform_application.h"
#include "app/platform_application_misc.h"

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

EngineApplication::EngineApplication(SharedRef<PlatformApplication> const InPlatformApplication)
    : PlatformApplication_(InPlatformApplication) {
}

} // namespace px
