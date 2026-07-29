// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// NRI
#include "NRI.h"
#include "Extensions/NRISwapChain.h"

namespace px {

class RHIContext;

struct RHISwapChainTexture {
    nri::Fence* acquireSemaphore{nullptr};
    nri::Fence* releaseSemaphore{nullptr};
    nri::Texture* texture{nullptr};
    nri::Descriptor* colorAttachment{nullptr};
    nri::Format attachmentFormat{nri::Format::UNKNOWN};
};

struct RHISwapChain {
    RHISwapChain(RHIContext& context, nri::Window const& window, uint16 sizeX, uint16 sizeY);

    void destroy();

    nri::SwapChain* swapChain{nullptr};
    nri::Format swapChainFormat{nri::Format::UNKNOWN};
    std::vector<RHISwapChainTexture> swapChainTexturesRhi;

  private:
    RHIContext& rhiContext_;
};

PX_ENGINE_API UniquePtr<RHISwapChain> rhiCreateSwapchain(RHIContext& context, nri::Window const& window, uint16 sizeX, uint16 sizeY);

struct RHIViewport {
    PX_ENGINE_API RHIViewport(RHIContext& context, void* osWindowHandle, uint16 sizeX, uint16 sizeY, bool isFullscreen);
    PX_ENGINE_API ~RHIViewport();

    PX_ENGINE_API void* getOsWindowHandle() { return osWindowHandle_; }
    PX_ENGINE_API SharedPtr<RHISwapChain> getSwapChain() { return swapChainRhi_; }
    PX_ENGINE_API UVector2 getSize() const { return {sizeX_, sizeY_}; }
    PX_ENGINE_API void resize(uint16 sizeX, uint16 sizeY, bool isFullscreen);

  private:
    RHIContext& rhiContext_;

    uint16 sizeX_{0};
    uint16 sizeY_{0};
    bool isFullscreen_{false};

    void* osWindowHandle_{nullptr};
    nri::Window window_;

    SharedPtr<RHISwapChain> swapChainRhi_{nullptr};
};

PX_ENGINE_API UniquePtr<RHIViewport> rhiCreateViewport(RHIContext& context, void* windowHandle, uint16 sizeX, uint16 sizeY, bool isFullscreen);

} // namespace px
