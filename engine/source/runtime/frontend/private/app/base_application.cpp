// © 2026 Pawel Mlynarz

#include "app/base_application.h"

// pxrendercore
#include "base_renderer.h"

namespace px {

SharedPtr<BaseApplication> BaseApplication::BaseApplicationInstance_{nullptr};

bool BaseApplication::InitializeRenderer(SharedPtr<BaseRenderer> Renderer) {
    Renderer_ = std::move(Renderer);
    return Renderer_->Initialize();
}

void BaseApplication::DestoryRenderer() {
    if (Renderer_) {
        Renderer_->Shutdown();
    }
    Renderer_.reset();
}

BaseRenderer& BaseApplication::GetRenderer() const {
    Assert(Renderer_ != nullptr);
    return *Renderer_;
}

} // namespace px
