// © 2026 Pawel Mlynarz

#include "rhi_resources.h"
#include "rhi_context.h"
#include "rhi_asserts.h"

namespace px {

namespace {

inline uint8 GetOptimalSwapChainTextureNum(RHIContext const& Context) {
    return Context.GetQueuedFrameNum() + 1;
}

void PrepareNRIWindowHandle(nri::Window& Window, void* OSWindowHandle) {
#if PLATFORM_WINDOWS
    Window.windows.hwnd = OSWindowHandle;
#else
#error Unsupported platform: Window handle not mapped.
#endif
}

} // namespace

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
RHISwapChain::RHISwapChain(RHIContext& Context, nri::Window const& Window, uint16 const SizeX, uint16 const SizeY)
    : RHIContext_(Context) {

    RHIInterface const& RHI{RHIContext_.GetRHI()};
    nri::Device* Device{Context.GetDevice()};

    nri::SwapChainDesc const SwapChainDesc{
        .window = Window,
        .queue = RHIContext_.GetGraphicsQueue(),
        .width = SizeX,
        .height = SizeY,
        .textureNum = GetOptimalSwapChainTextureNum(Context),
        .format = nri::SwapChainFormat::BT709_G22_8BIT,
        .flags = (RHIStaticContext::bVSync ? nri::SwapChainBits::VSYNC : nri::SwapChainBits::NONE) | nri::SwapChainBits::ALLOW_TEARING,
        .queuedFrameNum = RHIContext_.GetQueuedFrameNum()
    };

    RHI_ABORT_ON_FAILURE(RHIContext_.GetRHI().CreateSwapChain(*Device, SwapChainDesc, SwapChain))

    uint32_t SwapChainTextureNum{0};
    nri::Texture* const* SwapChainTextures{RHI.GetSwapChainTextures(*SwapChain, SwapChainTextureNum)};
    SwapChainFormat = RHI.GetTextureDesc(*SwapChainTextures[0]).format;

    for (uint32_t Idx{0}; Idx < SwapChainTextureNum; ++Idx) {
        nri::TextureViewDesc const TextureViewDesc{.texture = SwapChainTextures[Idx], .type = nri::TextureView::COLOR_ATTACHMENT, .format = SwapChainFormat};

        nri::Descriptor* ColorAttachment{nullptr};
        RHI_ABORT_ON_FAILURE(RHI.CreateTextureView(TextureViewDesc, ColorAttachment))

        nri::Fence* AcquireSemaphore{nullptr};
        RHI_ABORT_ON_FAILURE(RHI.CreateFence(*Device, nri::SWAPCHAIN_SEMAPHORE, AcquireSemaphore))

        nri::Fence* ReleaseSemaphore{nullptr};
        RHI_ABORT_ON_FAILURE(RHI.CreateFence(*Device, nri::SWAPCHAIN_SEMAPHORE, ReleaseSemaphore))

        RHISwapChainTexture const Texture{
            .AcquireSemaphore = AcquireSemaphore,
            .ReleaseSemaphore = ReleaseSemaphore,
            .Texture = SwapChainTextures[Idx],
            .ColorAttachment = ColorAttachment,
            .AttachmentFormat = SwapChainFormat
        };
        SwapChainTexturesRHI.emplace_back(Texture);
    }
}

void RHISwapChain::Destroy() {
    RHIInterface const& RHI{RHIContext_.GetRHI()};
    RHI.DeviceWaitIdle(RHIContext_.GetDevice());

    for (RHISwapChainTexture const& SwapChainTexture : SwapChainTexturesRHI) {
        RHI.DestroyFence(SwapChainTexture.AcquireSemaphore);
        RHI.DestroyFence(SwapChainTexture.ReleaseSemaphore);
        RHI.DestroyDescriptor(SwapChainTexture.ColorAttachment);
    }

    if (SwapChain) {
        RHI.DestroySwapChain(SwapChain);
        SwapChain = nullptr;
    }
}

UniquePtr<RHISwapChain> RHICreateSwapchain(RHIContext& Context, nri::Window const& Window, uint16 const SizeX, uint16 const SizeY) {
    UniquePtr SwapChain{MakeUnique<RHISwapChain>(Context, Window, SizeX, SizeY)};
    return SwapChain;
}

RHIViewport::RHIViewport(RHIContext& Context, void* const OSWindowHandle, uint16 const SizeX, uint16 const SizeY)
    : RHIContext_(Context), OSWindowHandle_(OSWindowHandle), SizeX_(SizeX), SizeY_(SizeY) {

    PrepareNRIWindowHandle(Window_, OSWindowHandle);

    Assert(RHIContext_.GetGraphicsQueue() != nullptr);

    SwapChainRHI_ = RHICreateSwapchain(RHIContext_, Window_, SizeX_, SizeY_);
}

RHIViewport::~RHIViewport() {
    if (SwapChainRHI_) {
        SwapChainRHI_->Destroy();
    }
}

UniquePtr<RHIViewport> RHICreateViewport(RHIContext& Context, void* const WindowHandle, uint16 const SizeX, uint16 const SizeY) {
    UniquePtr Viewport{MakeUnique<RHIViewport>(Context, WindowHandle, SizeX, SizeY)};
    return Viewport;
}

} // namespace px
