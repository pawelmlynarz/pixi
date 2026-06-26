// © 2026 Pawel Mlynarz

#include "app/base_application.h"

// pxrendercore
#include "base_renderer.h"

namespace px {

SharedPtr<BaseApplication> BaseApplication::baseApplicationInstance{nullptr};

bool BaseApplication::initializeRenderer(SharedPtr<BaseRenderer> renderer) {
    Renderer_ = std::move(renderer);
    return Renderer_->initialize();
}

void BaseApplication::destoryRenderer() {
    if (Renderer_) {
        Renderer_->shutdown();
    }
    Renderer_.reset();
}

BaseRenderer& BaseApplication::getRenderer() const {
    pxAssert(Renderer_ != nullptr);
    return *Renderer_;
}

} // namespace px
