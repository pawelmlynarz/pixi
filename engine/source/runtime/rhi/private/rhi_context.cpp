// © 2026 Pawel Mlynarz

// NOLINTBEGIN

#include "rhi_context.h"
#include "rhi_asserts.h"

// pxcore
#include "tools/asserts.h"

#include <array>

namespace px {

namespace {

using AdaptersDescList = std::array<nri::AdapterDesc, 2>;

AdaptersDescList RHIGetAdaptersDesc() {
    std::array<nri::AdapterDesc, 2> AdaptersDesc{};

    uint32 AdaptersDescSize{static_cast<uint32>(AdaptersDesc.size())};
    RHI_ABORT_ON_FAILURE(nri::nriEnumerateAdapters(AdaptersDesc.data(), AdaptersDescSize))

    return AdaptersDesc;
}

void RHICreateDevice(RHIContext const& Context, AdaptersDescList const& AdaptersDesc) {
    PX_TODO("Select best adapter.");
    int32 constexpr BestAdapterIdx{0};

    nri::DeviceCreationDesc const DeviceCreationDesc{
        .graphicsAPI = Context.GetBackend(),
        .adapterDesc = &AdaptersDesc[BestAdapterIdx],
        .vkBindingOffsets = RHIStaticContext::VkBindingOffsets,
        .enableNRIValidation = RHIStaticContext::bDebugNRI,
        .enableGraphicsAPIValidation = RHIStaticContext::bDebugAPI,
        .enableD3D11CommandBufferEmulation = RHIStaticContext::bD3D11EnableCommandBufferEmulation,
        .disableD3D12EnhancedBarriers = RHIStaticContext::bD3D12DisableEnhancedBarriers,
    };
    RHI_ABORT_ON_FAILURE(nri::nriCreateDevice(DeviceCreationDesc, Context.GetDevice()))
}

void RHIDestoryDevice(RHIContext const& Context) {
    nri::Device*& Device{Context.GetDevice()};
    nri::nriDestroyDevice(Device);
    Device = nullptr;
}

void RHICreateInterface(RHIContext const& Context) {
    RHIInterface& RHI{Context.GetRHI()};
    nri::Device const* const Device{Context.GetDevice()};

    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*Device, NRI_INTERFACE(nri::CoreInterface), RHI.As<nri::CoreInterface>()))
    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*Device, NRI_INTERFACE(nri::HelperInterface), RHI.As<nri::HelperInterface>()))
    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*Device, NRI_INTERFACE(nri::StreamerInterface), RHI.As<nri::StreamerInterface>()))
    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*Device, NRI_INTERFACE(nri::SwapChainInterface), RHI.As<nri::SwapChainInterface>()))
}

void RHICreateStreamer(RHIContext const& Context) {
    nri::StreamerDesc const StreamerDesc{
        .constantBufferMemoryLocation = nri::MemoryLocation::HOST_UPLOAD,
        .dynamicBufferMemoryLocation = nri::MemoryLocation::HOST_UPLOAD,
        .dynamicBufferDesc = {0, 0, nri::BufferUsageBits::VERTEX_BUFFER | nri::BufferUsageBits::INDEX_BUFFER},
        .queuedFrameNum = Context.GetQueuedFrameNum(),
    };

    RHI_ABORT_ON_FAILURE(Context.GetRHI().CreateStreamer(*Context.GetDevice(), StreamerDesc, Context.GetStreamer()))
}

void RHIDestroyStreamer(RHIContext const& Context) {
    RHIInterface& RHI{Context.GetRHI()};
    nri::Streamer*& Streamer{Context.GetStreamer()};

    if (RHI.HasStreamer()) {
        RHI.DestroyStreamer(Streamer);
        Streamer = nullptr;
    }
}

void RHICreateFrameFence(RHIContext const& Context) {
    RHI_ABORT_ON_FAILURE(Context.GetRHI().CreateFence(*Context.GetDevice(), 0, Context.GetFrameFence()))
}

void RHIDestroyFrameFence(RHIContext const& Context) {
    nri::Fence*& FrameFence{Context.GetFrameFence()};
    if (FrameFence != nullptr) {
        Context.GetRHI().DestroyFence(FrameFence);
        FrameFence = nullptr;
    }
}

void RHICreateQueuedFrames(RHIContext const& Context) {
    RHIInterface& RHI{Context.GetRHI()};
    Context.GetQueuedFrames().resize(Context.GetQueuedFrameNum());
    for (RHIQueuedFrame& Frame : Context.GetQueuedFrames()) {
        RHI_ABORT_ON_FAILURE(RHI.CreateCommandAllocator(*Context.GetGraphicsQueue(), Frame.CommandAllocator))
        RHI_ABORT_ON_FAILURE(RHI.CreateCommandBuffer(*Frame.CommandAllocator, Frame.CommandBuffer))
    }
}

void RHIDestoryQueuedFrames(RHIContext const& Context) {
    RHIInterface& RHI{Context.GetRHI()};

    for (RHIQueuedFrame& QueuedFrame : Context.GetQueuedFrames()) {
        if (QueuedFrame.CommandBuffer) {
            RHI.DestroyCommandBuffer(QueuedFrame.CommandBuffer);
            QueuedFrame.CommandBuffer = nullptr;
        }
        if (QueuedFrame.CommandAllocator) {
            RHI.DestroyCommandAllocator(QueuedFrame.CommandAllocator);
            QueuedFrame.CommandAllocator = nullptr;
        }
        if (QueuedFrame.ConstantBufferView) {
            RHI.DestroyDescriptor(QueuedFrame.ConstantBufferView);
            QueuedFrame.ConstantBufferView = nullptr;
        }
    }
}

void RHIGetCommandQueue(RHIContext const& Context) {
    RHI_ABORT_ON_FAILURE(Context.GetRHI().GetQueue(*Context.GetDevice(), nri::QueueType::GRAPHICS, 0, Context.GetGraphicsQueue()))
}

} // namespace

RHIContext::RHIContext(nri::GraphicsAPI const Backend)
    : Backend_(Backend),
      RHI_(MakeUnique<RHIInterface>()),
      Resources_(MakeUnique<RHIContextResources>()) {
}

void RHIContext::Initialize() {
    AdaptersDescList const AdapterDesc{RHIGetAdaptersDesc()};

    // Initializes backend, adapter, toolset, and creates a logical device.
    RHICreateDevice(*this, AdapterDesc);

    // Initializes RHI Interface.
    RHICreateInterface(*this);

    // Fetches Graphics command queue.
    RHIGetCommandQueue(*this);

    // Creates Streamer.
    RHICreateStreamer(*this);

    // Creates Frame Fence.
    RHICreateFrameFence(*this);

    // Creates Queued Frames.
    RHICreateQueuedFrames(*this);
}

void RHIContext::Shutdown() {
    RHI_->DeviceWaitIdle(GetDevice());

    // Destroy all owned resources.
    RHIDestoryQueuedFrames(*this);
    RHIDestroyStreamer(*this);
    RHIDestroyFrameFence(*this);
    RHIDestoryDevice(*this);
}

} // namespace px

// NOLINTEND
