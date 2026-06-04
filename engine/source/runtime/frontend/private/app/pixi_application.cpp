// © 2026 Pawel Mlynarz

#include "app/pixi_application.h"
#include "base_renderer.h"
#include "widgets/swindow.h"

// pxcore
#include "app/platform_application.h"
#include "app/platform_application_misc.h"
#include "input/engine_input_system.h"
#include "window/generic_window.h"

namespace px {

SharedPtr<SimpleApplication> SimpleApplication::ApplicationInstance_{nullptr};

namespace {

SharedRef<GenericWindow> CreatePlatformWindow(SharedRef<SWindow> const& SWindow, SharedRef<PlatformApplication> const& PlatformApplication) {
    GenericWindowDefinition const WindowDefinition{
        .Title = SWindow->GetTitle(),
        .WidthDesired = static_cast<uint16>(SWindow->GetSize().x),
        .HeightDesired = static_cast<uint16>(SWindow->GetSize().y),
        .bDecorated = SWindow->GetDecorated(),
        .bResizable = SWindow->GetResizable()
    };

    SharedRef<GenericWindow> const PlatformWindow{PlatformApplication->CreatePlatformWindow()};
    PlatformApplication->InitializeWindow(PlatformWindow, WindowDefinition);

    SWindow->SetNativeWindow(PlatformWindow.ToWeak());

    return PlatformWindow;
}

} // namespace

SimpleApplication::SimpleApplication(SharedRef<PlatformApplication> const PlatformApplication)
    : PlatformApplication_(PlatformApplication) {
    PlatformApplication_->Initialize();
    PlatformApplication_->SetMessageHandler(MakeShared<EngineInputSystem>(PlatformApplication_));
}

SimpleApplication::~SimpleApplication() {
}

SimpleApplication& SimpleApplication::CreateApplication() {
    return CreateApplication(SharedRef<PlatformApplication>(PlatformApplicationMisc::CreateApplication()));
}

SimpleApplication& SimpleApplication::CreateApplication(SharedRef<class PlatformApplication> const PlatformApplication) {
    ApplicationInstance_ = MakeShared<SimpleApplication>(PlatformApplication);
    BaseApplicationInstance_ = ApplicationInstance_;
    return *ApplicationInstance_;
}

void SimpleApplication::ShutdownApplication() {
    ApplicationInstance_->DestoryRenderer();
    ApplicationInstance_->PlatformApplication_->Shutdown();
    ApplicationInstance_.reset();
}

bool SimpleApplication::IsInitialized() {
    return ApplicationInstance_ != nullptr;
}

void SimpleApplication::Tick(float const Dt) {
    PlatformApplication_->PollMessages();

    if (Renderer_)
        Renderer_->Tick(Dt);

    DrawWindows();
}

bool SimpleApplication::AddWindow(SharedRef<SWindow> SWindow, bool const bShowImmediately) {
    Windows_.emplace_back(SWindow);
    SharedRef const Window{CreatePlatformWindow(SWindow, PlatformApplication_)};

    if (bShowImmediately)
        SWindow->ShowWindow();

    return true;
}

void SimpleApplication::DrawWindows() const {
    for (auto& Window : Windows_) {
        Window->PaintWindow();
    }
}

} // namespace px
