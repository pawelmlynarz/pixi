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
    RHISwapChain(RHIContext& Context, nri::Window const& Window, uint16 const SizeX, uint16 const SizeY);

    void Destroy();

    nri::SwapChain* SwapChain{nullptr};
    nri::Format SwapChainFormat{nri::Format::UNKNOWN};
    std::vector<RHISwapChainTexture> SwapChainTexturesRHI{};

  private:
    RHIContext& RHIContext_;
};

PXRHI_API UniquePtr<RHISwapChain> RHICreateSwapchain(RHIContext& Context, nri::Window const& Window, uint16 const SizeX, uint16 const SizeY);

struct RHIViewport {
    PXRHI_API RHIViewport(RHIContext& Context, void* const OSWindowHandle, uint16 const SizeX, uint16 const SizeY);
    PXRHI_API ~RHIViewport();

    PXRHI_API void* GetOSWindowHandle() { return OSWindowHandle_; }
    PXRHI_API SharedPtr<RHISwapChain> GetSwapChain() { return SwapChainRHI_; }
    PXRHI_API UVector2 GetSize() { return {SizeX_, SizeY_}; }

  private:
    RHIContext& RHIContext_;

    uint16 SizeX_{0};
    uint16 SizeY_{0};

    void* OSWindowHandle_{nullptr};
    nri::Window Window_;

    SharedPtr<RHISwapChain> SwapChainRHI_{nullptr};
};

PXRHI_API UniquePtr<RHIViewport> RHICreateViewport(RHIContext& Context, void* const WindowHandle, uint16 const SizeX, uint16 const SizeY);

} // namespace px
