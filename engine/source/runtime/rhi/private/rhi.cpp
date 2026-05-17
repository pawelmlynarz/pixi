// © 2026 Pawel Mlynarz

#include "rhi.h"
#include "rhi_asserts.h"
#include "rhi_interface.h"

// pxcore
#include "common/types.h"
#include "tools/asserts.h"
#include "tools/utility.h"

// NRI
#include "NRI.h"
#include "Extensions/NRIDeviceCreation.h"
#include "Extensions/NRIHelper.h"
#include "Extensions/NRIStreamer.h"

#include <array>

namespace px {

namespace {

struct RHIDeviceDeleter {
    void operator()(nri::Device* Device) const {
        nri::nriDestroyDevice(Device);
    }
};

struct RHIContext {
    RHIInterface RHI{};
    
    UniquePtr<nri::Device, RHIDeviceDeleter> Device{nullptr};
    UniquePtr<nri::Streamer> Streamer{nullptr};
    UniquePtr<nri::Queue> GraphicsQueue{nullptr};
    UniquePtr<nri::Fence> FrameFence{nullptr};

    nri::AllocationCallbacks AllocationCallbacks{};
    nri::GraphicsAPI Backend{nri::GraphicsAPI::NONE};
    
    static constexpr bool bDebugAPI{false};
    static constexpr bool bDebugNRI{false};

    static constexpr bool bD3D11EnableCommandBufferEmulation{false};
    static constexpr bool bD3D12DisableEnhancedBarriers{false};
    static constexpr bool bVSync{false};

    static constexpr nri::VKBindingOffsets VkBindingOffsets{0, 128, 32, 64};
} Context;

bool bInitialized{false};

nri::GraphicsAPI GetBackendForPlatform() {
#if PLATFORM_WINDOWS
    PX_TODO("Make possible to override via command line.");
    return nri::GraphicsAPI::VK;
#else
#error Unsupported platform: no RHI specified.
#endif
}

using AdaptersDescList = std::array<nri::AdapterDesc, 2>;

AdaptersDescList GetAdaptersDesc() {
    std::array<nri::AdapterDesc, 2> AdaptersDesc{};

    uint32_t AdaptersDescSize{static_cast<uint32_t>(AdaptersDesc.size())};
    NRI_ABORT_ON_FAILURE(nri::nriEnumerateAdapters(AdaptersDesc.data(), AdaptersDescSize))
    
    return AdaptersDesc;
}

uint8_t GetQueuedFrameNum() {
    return Context.bVSync ? 2 : 3;
}

void CreateRHIDevice(AdaptersDescList const& AdaptersDesc) {

    int32 const AdapterIdx{0};

    nri::DeviceCreationDesc DeviceCreationDesc{
        .graphicsAPI = Context.Backend,
        .adapterDesc = &AdaptersDesc[AdapterIdx],
        .allocationCallbacks = Context.AllocationCallbacks,
        .vkBindingOffsets = RHIContext::VkBindingOffsets,
        .enableNRIValidation = RHIContext::bDebugNRI,
        .enableGraphicsAPIValidation = RHIContext::bDebugAPI,
        .enableD3D11CommandBufferEmulation = RHIContext::bD3D11EnableCommandBufferEmulation,
        .disableD3D12EnhancedBarriers = RHIContext::bD3D12DisableEnhancedBarriers,
    };

    nri::Device* DeviceRaw{nullptr};
    NRI_ABORT_ON_FAILURE(nri::nriCreateDevice(DeviceCreationDesc, DeviceRaw))
    Context.Device.reset(DeviceRaw);
}

void CreateRHIInterface() {
    NRI_ABORT_ON_FAILURE(nri::nriGetInterface(*Context.Device, NRI_INTERFACE(nri::CoreInterface), static_cast<nri::CoreInterface*>(&Context.RHI)))
    NRI_ABORT_ON_FAILURE(nri::nriGetInterface(*Context.Device, NRI_INTERFACE(nri::HelperInterface), static_cast<nri::HelperInterface*>(&Context.RHI)))
    NRI_ABORT_ON_FAILURE(nri::nriGetInterface(*Context.Device, NRI_INTERFACE(nri::StreamerInterface), static_cast<nri::StreamerInterface*>(&Context.RHI)))
    NRI_ABORT_ON_FAILURE(nri::nriGetInterface(*Context.Device, NRI_INTERFACE(nri::SwapChainInterface), static_cast<nri::SwapChainInterface*>(&Context.RHI)))
}

void CreateStreamer() {
    nri::StreamerDesc StreamerDesc {
        .constantBufferMemoryLocation = nri::MemoryLocation::HOST_UPLOAD,
        .dynamicBufferMemoryLocation = nri::MemoryLocation::HOST_UPLOAD,
        .dynamicBufferDesc = {0, 0, nri::BufferUsageBits::VERTEX_BUFFER | nri::BufferUsageBits::INDEX_BUFFER},
        .queuedFrameNum = GetQueuedFrameNum(),
    };
    
    nri::Streamer* StreamerRaw{nullptr};
    NRI_ABORT_ON_FAILURE(Context.RHI.CreateStreamer(*Context.Device, StreamerDesc, StreamerRaw));
    Context.Streamer.reset(StreamerRaw);
}

void CreateCommandQueue() {
    nri::Queue* GraphicsQueueRaw{nullptr};
    NRI_ABORT_ON_FAILURE(Context.RHI.GetQueue(*Context.Device, nri::QueueType::GRAPHICS, 0, GraphicsQueueRaw))
    Context.GraphicsQueue.reset(GraphicsQueueRaw);
}

void CreateFrameFence() {
    nri::Fence* FrameFenceRaw{nullptr};
    NRI_ABORT_ON_FAILURE(Context.RHI.CreateFence(*Context.Device, 0, FrameFenceRaw));
    Context.FrameFence.reset(FrameFenceRaw);
}

} // namespace         

void InitializeRHI() {
    PX_ASSERT(!bInitialized);

    Context.Backend = GetBackendForPlatform();
    
#if _DEBUG
    PX_TODO("Debug allocator.");
    Context.AllocationCallbacks = nri::AllocationCallbacks(); 
#endif

    AdaptersDescList const AdapterDesc{GetAdaptersDesc()};
    CreateRHIDevice(AdapterDesc);
    
    CreateRHIInterface();
    CreateStreamer();
    CreateCommandQueue();
    CreateFrameFence();
    
    bInitialized = true;
}

void ShutdownRHI() {
    PX_ASSERT(bInitialized);
    
    RHIInterface& RHI {Context.RHI};
    
    RHI.DestroyFence(Context.FrameFence.get());
    Context.FrameFence.reset();
    
    if (RHI.HasStreamer()) {
        RHI.DestroyStreamer(Context.Streamer.get());
        Context.Streamer.reset();
    }
    
    Context.Device.reset();
    bInitialized = false;
}

nri::GraphicsAPI GetBackend() {
    return Context.Backend;
}

} // namespace px
