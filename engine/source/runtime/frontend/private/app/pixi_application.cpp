// © 2026 Pawel Mlynarz

#include "app/pixi_application.h"
#include "rendering/renderer.h"
#include "window/window.h"
#include "input/input_system.h"
#include "platform/generic_platform/generic_application.h"
#include "platform/generic_platform/generic_window.h"
#include "hal/platform_application_misc.h"

namespace px {

namespace {

SharedPtr<PixiApplication> sApplication{nullptr};

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

PixiApplication::PixiApplication(SharedRef<PlatformApplication> const& platformApplication)
    : platformApplication_(platformApplication) {
    platformApplication_->initialize();
    platformApplication_->setMessageHandler(makeShared<InputSystem>(platformApplication_.toPtr()));
}

PixiApplication::~PixiApplication() = default;

PixiApplication& PixiApplication::createApplication() {
    return createApplication(SharedRef<PlatformApplication>(PlatformApplicationMisc::createApplication()));
}

PixiApplication& PixiApplication::createApplication(SharedRef<PlatformApplication> const& platformApplication) {
    sApplication = makeShared<PixiApplication>(platformApplication);
    return *sApplication;
}

void PixiApplication::shutdownApplication() {
    sApplication->destroyRenderer();
    sApplication->platformApplication_->shutdown();
    sApplication.reset();
}

bool PixiApplication::isInitialized() {
    return sApplication != nullptr;
}

PixiApplication& PixiApplication::get() {
    pxAssert(sApplication.get() != nullptr);
    return *sApplication;
}

bool PixiApplication::initializeRenderer(SharedPtr<Renderer> renderer) {
    renderer_ = std::move(renderer);
    return renderer_->initialize();
}

void PixiApplication::destroyRenderer() {
    if (renderer_) {
        renderer_->shutdown();
    }
    renderer_.reset();
}

Renderer& PixiApplication::getRenderer() const {
    pxAssert(renderer_ != nullptr);
    return *renderer_;
}

void PixiApplication::tick(float const dt) {
    platformApplication_->pollMessages();

    if (renderer_) {
        renderer_->tick(dt);
    }

    drawWindows();
}

bool PixiApplication::addWindow(SharedRef<Window> window, bool const bShowImmediately) {
    windows_.emplace_back(window);
    SharedRef const platformWindow{createPlatformWindow(window, platformApplication_)};

    if (bShowImmediately) {
        window->showWindow();
    }

    return true;
}

SharedPtr<Window> PixiApplication::findWindowByPlatformWindow(SharedRef<PlatformWindow> const& platformWindow) {
    auto const it = std::ranges::find_if(windows_, [&](SharedRef<Window> const& window) {
        return window->getNativeWindow() == platformWindow;
    });
    return it != windows_.end() ? it->toPtr() : nullptr;
}

void PixiApplication::drawWindows() const {
    for (auto const& window : windows_) {
        window->paintWindow();
    }
}

} // namespace px
