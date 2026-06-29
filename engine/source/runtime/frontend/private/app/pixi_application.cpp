// © 2026 Pawel Mlynarz

#include "app/pixi_application.h"
#include "base_renderer.h"
#include "window/window.h"
#include "input/input_system.h"
#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "hal/platform_application_misc.h"

namespace px {

SharedPtr<SimpleApplication> SimpleApplication::applicationInstance{nullptr};

namespace {

SharedRef<PlatformWindow> createPlatformWindow(SharedRef<Window> const& window, SharedRef<PlatformApplication> const& platformApplication) {
    PlatformWindowDefinition const windowDefinition{
        .title = window->getTitle(),
        .widthDesired = static_cast<uint16>(window->getSize().x),
        .heightDesired = static_cast<uint16>(window->getSize().y),
        .decorated = window->getDecorated(),
        .resizable = window->getResizable()
    };

    SharedRef<PlatformWindow> const platformWindow{platformApplication->createPlatformWindow()};
    platformApplication->initializeWindow(platformWindow, windowDefinition);

    window->setNativeWindow(platformWindow.toWeak());

    return platformWindow;
}

} // namespace

SimpleApplication::SimpleApplication(SharedRef<PlatformApplication> const& platformApplication)
    : platformApplication_(platformApplication) {
    platformApplication_->initialize();
    platformApplication_->setMessageHandler(makeShared<InputSystem>(platformApplication_));
}

SimpleApplication::~SimpleApplication() = default;

SimpleApplication& SimpleApplication::createApplication() {
    return createApplication(SharedRef<PlatformApplication>(PlatformApplicationMisc::createApplication()));
}

SimpleApplication& SimpleApplication::createApplication(SharedRef<class PlatformApplication> const& platformApplication) {
    applicationInstance = makeShared<SimpleApplication>(platformApplication);
    baseApplicationInstance = applicationInstance;
    return *applicationInstance;
}

void SimpleApplication::shutdownApplication() {
    applicationInstance->destoryRenderer();
    applicationInstance->platformApplication_->shutdown();
    applicationInstance.reset();
}

bool SimpleApplication::isInitialized() {
    return applicationInstance != nullptr;
}

void SimpleApplication::tick(float const dt) {
    platformApplication_->pollMessages();

    if (Renderer_) {
        Renderer_->tick(dt);
    }

    drawWindows();
}

bool SimpleApplication::addWindow(SharedRef<Window> window, bool const bShowImmediately) {
    windows_.emplace_back(window);
    SharedRef const platformWindow{createPlatformWindow(window, platformApplication_)};

    if (bShowImmediately) {
        window->showWindow();
    }

    return true;
}

SharedPtr<Window> SimpleApplication::findWindowByPlatformWindow(SharedRef<PlatformWindow> const& platformWindow) {
    auto const it = std::ranges::find_if(windows_, [&](SharedRef<Window> const& window) {
        return window->getNativeWindow() == platformWindow;
    });
    return it != windows_.end() ? it->toPtr() : nullptr;
}

void SimpleApplication::drawWindows() const {
    for (auto const& window : windows_) {
        window->paintWindow();
    }
}

} // namespace px
