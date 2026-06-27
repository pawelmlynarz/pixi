// © 2026 Pawel Mlynarz

#pragma once

// pxcore
#include "tools/utility.h"
#include "common/types.h"

// NRI
#include "NRI.h"
#include "rhi_module.h"
#include "Extensions/NRISwapChain.h"

namespace px {

class RHIContext;

struct RHISwapChainTexture {
    nri::Fence* AcquireSemaphore{nullptr};
    nri::Fence* ReleaseSemaphore{nullptr};
    nri::Texture* Texture{nullptr};
    nri::Descriptor* ColorAttachment{nullptr};
    nri::Format AttachmentFormat{nri::Format::UNKNOWN};
};

struct RHISwapChain {
    RHISwapChain(RHIContext& context, nri::Window const& window, uint16 sizeX, uint16 sizeY);

    void destroy();

    nri::SwapChain* SwapChain{nullptr};
    nri::Format SwapChainFormat{nri::Format::UNKNOWN};
    std::vector<RHISwapChainTexture> SwapChainTexturesRHI;

  private:
    RHIContext& rhiContext_;
};

PXRHI_API UniquePtr<RHISwapChain> rhiCreateSwapchain(RHIContext& context, nri::Window const& window, uint16 sizeX, uint16 sizeY);

struct RHIViewport {
    PXRHI_API RHIViewport(RHIContext& context, void* osWindowHandle, uint16 sizeX, uint16 sizeY, bool isFullscreen);
    PXRHI_API ~RHIViewport();

    PXRHI_API void* getOsWindowHandle() { return osWindowHandle_; }
    PXRHI_API SharedPtr<RHISwapChain> getSwapChain() { return swapChainRhi_; }
    PXRHI_API UVector2 getSize() const { return {sizeX_, sizeY_}; }
    PXRHI_API void resize(uint16 sizeX, uint16 sizeY, bool isFullscreen);

  private:
    RHIContext& rhiContext_;

    uint16 sizeX_{0};
    uint16 sizeY_{0};
    bool isFullscreen_{false};

    void* osWindowHandle_{nullptr};
    nri::Window window_;

    SharedPtr<RHISwapChain> swapChainRhi_{nullptr};
};

PXRHI_API UniquePtr<RHIViewport> rhiCreateViewport(RHIContext& context, void* windowHandle, uint16 sizeX, uint16 sizeY, bool isFullscreen);

} // namespace px
