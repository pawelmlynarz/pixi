// © 2026 Pawel Mlynarz

#include "renderer.h"

// pxrendercore
#include "render_resource.h"
#include "rhi.h"
#include "rhi_resources.h"
#include "widgets/swindow.h"
#include "window/generic_window.h"

namespace px {

struct RenderViewportInfo : public RenderResource {
    void* OSWindow{nullptr};
    SharedPtr<RHIViewport> RHIViewport{nullptr};
};

struct Renderer::Impl {
    ~Impl() = default;

    using ViewportInfoMap = std::unordered_map<SharedRef<SWindow>, UniquePtr<RenderViewportInfo>>;
    ViewportInfoMap WindowToViewportInfo;
};

Renderer::Renderer()
    : Impl_(MakeUnique<Impl>()) {
}

Renderer::~Renderer() {
}

bool Renderer::Initialize() {
    return true;
}

void Renderer::Shutdown() {
    Impl_->WindowToViewportInfo.clear();
}

SharedPtr<RHIViewport> Renderer::GetViewportResource(SharedRef<SWindow> Window) const {
    auto const& Map{Impl_->WindowToViewportInfo};

    if (auto It{Map.find(Window)}; It != Map.end()) {
        return It->second->RHIViewport;
    }
    return nullptr;
}

void Renderer::CreateViewport(SharedRef<SWindow> Window) {
    UniquePtr ViewInfo{MakeUnique<RenderViewportInfo>()};

    void* const OSWindow{Window->GetNativeWindow()->GetOSWindowHandle().Handle};
    Assert(OSWindow != nullptr);

    ViewInfo->OSWindow = OSWindow;
    ViewInfo->RHIViewport = RHICreateViewport(
        GetRHIContext(),
        ViewInfo->OSWindow,
        static_cast<uint16>(Window->GetSize().x), static_cast<uint16>(Window->GetSize().y)
    );

    Impl_->WindowToViewportInfo.emplace(Window, std::move(ViewInfo));
}

} // namespace px
