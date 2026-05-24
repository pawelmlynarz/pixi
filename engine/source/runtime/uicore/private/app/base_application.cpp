// © 2026 Pawel Mlynarz

#include "app/base_application.h"
#include "rendering/base_renderer.h"

namespace px {

SharedPtr<BaseApplication> BaseApplication::BaseApplicationInstance_{nullptr};

BaseApplication::~BaseApplication() {
    PX_ASSERT_MSG(Renderer_ == nullptr, "Renderer should be destroyed manually during shutdown flow.");
}

bool BaseApplication::InitializeRenderer(SharedPtr<BaseRenderer> Renderer) {
    Renderer_ = std::move(Renderer);
    return Renderer_->Initialize();
}

void BaseApplication::DestoryRenderer() {
    if (Renderer_)
        Renderer_->Shutdown();
}

BaseRenderer& BaseApplication::GetRenderer() const {
    PX_ASSERT(Renderer_ != nullptr);
    return *Renderer_;
}

} // namespace px
