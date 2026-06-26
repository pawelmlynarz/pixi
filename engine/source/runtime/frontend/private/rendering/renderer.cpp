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
#include "widgets/swindow.h"
#include "platform/generic_platform/generic_window.h"

namespace px {

namespace {

struct RenderViewportInfo : public RenderResource {
    void* OSWindow{nullptr};
    SharedPtr<RHIViewport> RHIViewport{nullptr};
};

} // namespace

struct Renderer::Impl {
    ~Impl() = default;

    using ViewportInfoMap = std::unordered_map<SharedRef<SWindow>, UniquePtr<RenderViewportInfo>>;
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
#if WITH_IMGUI
    impl_->ImGuiRenderer.initialize(getRhiContext().getDevice());
#endif
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

SharedPtr<RHIViewport> Renderer::getViewportResource(SharedRef<SWindow> window) const {
    auto const& map{impl_->WindowToViewportInfo};

    if (auto it{map.find(window)}; it != map.end()) {
        return it->second->RHIViewport;
    }
    return nullptr;
}

void Renderer::createViewport(SharedRef<SWindow> window) {
    UniquePtr viewInfo{makeUnique<RenderViewportInfo>()};

    void* const osWindow{window->getNativeWindow()->getOsWindowHandle().Handle};
    pxAssert(osWindow != nullptr);

    viewInfo->OSWindow = osWindow;
    viewInfo->RHIViewport = rhiCreateViewport(
        getRhiContext(),
        viewInfo->OSWindow,
        static_cast<uint16>(window->getSize().x), static_cast<uint16>(window->getSize().y)
    );

    impl_->WindowToViewportInfo.emplace(window, std::move(viewInfo));
}

#if WITH_IMGUI
ImGuiRenderer& Renderer::getImGuiRenderer() {
    return impl_->ImGuiRenderer;
}
#endif

} // namespace px
