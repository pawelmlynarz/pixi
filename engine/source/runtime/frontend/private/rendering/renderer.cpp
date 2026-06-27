// © 2026 Pawel Mlynarz

#include "rendering/renderer.h"
#if WITH_IMGUI
#include "rendering/imgui_renderer.h"
#endif

// pxrendercore
#include "render_resource.h"
#include "rhi.h"
#include "rhi_context.h"
#include "rhi_resources.h"
#include "window/window.h"
#include "platform/generic_platform/generic_window.h"
#include "hal/platform_properties.h"

namespace px {

namespace {

struct RenderViewportInfo : public RenderResource {
    void* OSWindow{nullptr};
    SharedPtr<RHIViewport> RHIViewport{nullptr};
};

bool isViewportFullscreen(SharedRef<Window> const& window) {
    if constexpr (PlatformProperties::supportsWindowedMode()) {
        if (WITH_EDITOR) {
            return false;
        }
        pxToDo("&& window.getWindowMode() == EWindowMode::Fullscreen");
        return window->getNativeWindow()->isFullscreenSupported();
    } else {
        return true;
    }
}

} // namespace

struct Renderer::Impl {
    ~Impl() = default;

    using ViewportInfoMap = std::unordered_map<SharedRef<Window>, UniquePtr<RenderViewportInfo>>;
    ViewportInfoMap WindowToViewportInfo;
#if WITH_IMGUI
    ImGuiRenderer ImGuiRenderer;
#endif
};

Renderer::Renderer()
    : impl_(makeUnique<Impl>()) {
}

Renderer::~Renderer() = default;

bool Renderer::initialize() {
    return true;
}

void Renderer::shutdown() {
#if WITH_IMGUI
    impl_->ImGuiRenderer.shutdown();
#endif
    impl_->WindowToViewportInfo.clear();
}

void Renderer::tick(float const dt) {
#if WITH_IMGUI
    impl_->ImGuiRenderer.tick(dt);
#endif
}

SharedPtr<RHIViewport> Renderer::getViewportResource(SharedRef<Window> window) const {
    auto const& map{impl_->WindowToViewportInfo};

    if (auto it{map.find(window)}; it != map.end()) {
        return it->second->RHIViewport;
    }
    return nullptr;
}

void Renderer::createViewport(SharedRef<Window> window) {
    UniquePtr viewInfo{makeUnique<RenderViewportInfo>()};

    void* const osWindow{window->getNativeWindow()->getOsWindowHandle().Handle};
    pxAssert(osWindow != nullptr);
    UVector2 const windowSize{window->getSize()};

    viewInfo->OSWindow = osWindow;
    viewInfo->RHIViewport = rhiCreateViewport(
        getRhiContext(),
        viewInfo->OSWindow,
        static_cast<uint16>(windowSize.x), static_cast<uint16>(windowSize.y),
        isViewportFullscreen(window)
    );

    impl_->WindowToViewportInfo.emplace(window, std::move(viewInfo));

#if WITH_IMGUI
    if (!impl_->ImGuiRenderer.hasUserInterface()) {
        impl_->ImGuiRenderer.initialize(getRhiContext().getDevice(), windowSize);
    }
#endif
}

void Renderer::requestResizeViewport(SharedRef<Window> window, uint16 sizeX, uint16 sizeY) {
    if (auto& viewInfo{impl_->WindowToViewportInfo.at(window)}) {
        viewInfo->RHIViewport->resize(
            sizeX, sizeY, isViewportFullscreen(window)
        );
    }
#if WITH_IMGUI
    impl_->ImGuiRenderer.requestResizeDisplaySize({sizeX, sizeY});
#endif
}

void Renderer::flushCommands() const {
    getRhiContext().waitIdle();
}

#if WITH_IMGUI
ImGuiRenderer& Renderer::getImGuiRenderer() {
    return impl_->ImGuiRenderer;
}
#endif

} // namespace px
