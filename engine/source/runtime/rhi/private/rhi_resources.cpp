// © 2026 Pawel Mlynarz

#include "rhi_resources.h"
#include "rhi_context.h"
#include "rhi_asserts.h"

namespace px {

namespace {

inline uint8 getOptimalSwapChainTextureNum() {
    return px::RHIContext::getQueuedFrameNum() + 1;
}

void prepareNriWindowHandle(nri::Window& window, void* osWindowHandle) {
#if PLATFORM_WINDOWS
    window.windows.hwnd = osWindowHandle;
#else
#error Unsupported platform: Window handle not mapped.
#endif
}

} // namespace

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
RHISwapChain::RHISwapChain(RHIContext& context, nri::Window const& window, uint16 const sizeX, uint16 const sizeY)
    : rhiContext_(context) {

    RHIInterface const& rhi{rhiContext_.getRhi()};
    nri::Device* device{context.getDevice()};

    nri::SwapChainDesc const swapChainDesc{
        .window = window,
        .queue = rhiContext_.getGraphicsQueue(),
        .width = sizeX,
        .height = sizeY,
        .textureNum = getOptimalSwapChainTextureNum(),
        .format = nri::SwapChainFormat::BT709_G22_8BIT,
        .flags = (RHIStaticContext::bVSync ? nri::SwapChainBits::VSYNC : nri::SwapChainBits::NONE) | nri::SwapChainBits::ALLOW_TEARING,
        .queuedFrameNum = px::RHIContext::getQueuedFrameNum()
    };

    RHI_ABORT_ON_FAILURE(rhiContext_.getRhi().CreateSwapChain(*device, swapChainDesc, SwapChain))

    uint32_t swapChainTextureNum{0};
    nri::Texture* const* swapChainTextures{rhi.GetSwapChainTextures(*SwapChain, swapChainTextureNum)};
    SwapChainFormat = rhi.GetTextureDesc(*swapChainTextures[0]).format;

    for (uint32_t idx{0}; idx < swapChainTextureNum; ++idx) {
        nri::TextureViewDesc const textureViewDesc{.texture = swapChainTextures[idx], .type = nri::TextureView::COLOR_ATTACHMENT, .format = SwapChainFormat};

        nri::Descriptor* colorAttachment{nullptr};
        RHI_ABORT_ON_FAILURE(rhi.CreateTextureView(textureViewDesc, colorAttachment))

        nri::Fence* acquireSemaphore{nullptr};
        RHI_ABORT_ON_FAILURE(rhi.CreateFence(*device, nri::SWAPCHAIN_SEMAPHORE, acquireSemaphore))

        nri::Fence* releaseSemaphore{nullptr};
        RHI_ABORT_ON_FAILURE(rhi.CreateFence(*device, nri::SWAPCHAIN_SEMAPHORE, releaseSemaphore))

        RHISwapChainTexture const texture{
            .AcquireSemaphore = acquireSemaphore,
            .ReleaseSemaphore = releaseSemaphore,
            .Texture = swapChainTextures[idx],
            .ColorAttachment = colorAttachment,
            .AttachmentFormat = SwapChainFormat
        };
        SwapChainTexturesRHI.emplace_back(texture);
    }
}

void RHISwapChain::destroy() {
    RHIInterface const& rhi{rhiContext_.getRhi()};
    rhi.DeviceWaitIdle(rhiContext_.getDevice());

    for (RHISwapChainTexture const& swapChainTexture : SwapChainTexturesRHI) {
        rhi.DestroyFence(swapChainTexture.AcquireSemaphore);
        rhi.DestroyFence(swapChainTexture.ReleaseSemaphore);
        rhi.DestroyDescriptor(swapChainTexture.ColorAttachment);
    }

    if (SwapChain) {
        rhi.DestroySwapChain(SwapChain);
        SwapChain = nullptr;
    }
}

UniquePtr<RHISwapChain> rhiCreateSwapchain(RHIContext& context, nri::Window const& window, uint16 const sizeX, uint16 const sizeY) {
    UniquePtr swapChain{makeUnique<RHISwapChain>(context, window, sizeX, sizeY)};
    return swapChain;
}

RHIViewport::RHIViewport(RHIContext& context, void* const osWindowHandle, uint16 const sizeX, uint16 const sizeY)
    : rhiContext_(context), osWindowHandle_(osWindowHandle), sizeX_(sizeX), sizeY_(sizeY) {

    prepareNriWindowHandle(window_, osWindowHandle);

    pxAssert(rhiContext_.getGraphicsQueue() != nullptr);

    swapChainRhi_ = rhiCreateSwapchain(rhiContext_, window_, sizeX_, sizeY_);
}

RHIViewport::~RHIViewport() {
    if (swapChainRhi_) {
        swapChainRhi_->destroy();
    }
}

UniquePtr<RHIViewport> rhiCreateViewport(RHIContext& context, void* const windowHandle, uint16 const sizeX, uint16 const sizeY) {
    UniquePtr viewport{makeUnique<RHIViewport>(context, windowHandle, sizeX, sizeY)};
    return viewport;
}

} // namespace px
