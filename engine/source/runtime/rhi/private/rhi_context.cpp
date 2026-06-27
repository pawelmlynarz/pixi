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
    pxToDo("Select best adapter.");
    int32 constexpr BestAdapterIdx{0};

    nri::DeviceCreationDesc const DeviceCreationDesc{
        .graphicsAPI = Context.getBackend(),
        .adapterDesc = &AdaptersDesc[BestAdapterIdx],
        .vkBindingOffsets = RHIStaticContext::vkBindingOffsets,
        .enableNRIValidation = RHIStaticContext::bDebugNri,
        .enableGraphicsAPIValidation = RHIStaticContext::bDebugApi,
        .enableD3D11CommandBufferEmulation = RHIStaticContext::bD3D11EnableCommandBufferEmulation,
        .disableD3D12EnhancedBarriers = RHIStaticContext::bD3D12DisableEnhancedBarriers,
    };
    RHI_ABORT_ON_FAILURE(nri::nriCreateDevice(DeviceCreationDesc, Context.getDevice()))
}

void RHIDestoryDevice(RHIContext const& Context) {
    nri::Device*& Device{Context.getDevice()};
    nri::nriDestroyDevice(Device);
    Device = nullptr;
}

void RHICreateInterface(RHIContext const& Context) {
    RHIInterface& RHI{Context.getRhi()};
    nri::Device const* const Device{Context.getDevice()};

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
        .queuedFrameNum = Context.getQueuedFrameNum(),
    };

    RHI_ABORT_ON_FAILURE(Context.getRhi().CreateStreamer(*Context.getDevice(), StreamerDesc, Context.getStreamer()))
}

void RHIDestroyStreamer(RHIContext const& Context) {
    RHIInterface& RHI{Context.getRhi()};
    nri::Streamer*& Streamer{Context.getStreamer()};

    if (RHI.HasStreamer()) {
        RHI.DestroyStreamer(Streamer);
        Streamer = nullptr;
    }
}

void RHICreateFrameFence(RHIContext const& Context) {
    RHI_ABORT_ON_FAILURE(Context.getRhi().CreateFence(*Context.getDevice(), 0, Context.getFrameFence()))
}

void RHIDestroyFrameFence(RHIContext const& Context) {
    nri::Fence*& FrameFence{Context.getFrameFence()};
    if (FrameFence != nullptr) {
        Context.getRhi().DestroyFence(FrameFence);
        FrameFence = nullptr;
    }
}

void RHICreateQueuedFrames(RHIContext const& Context) {
    RHIInterface& RHI{Context.getRhi()};
    Context.getQueuedFrames().resize(Context.getQueuedFrameNum());
    for (RHIQueuedFrame& Frame : Context.getQueuedFrames()) {
        RHI_ABORT_ON_FAILURE(RHI.CreateCommandAllocator(*Context.getGraphicsQueue(), Frame.CommandAllocator))
        RHI_ABORT_ON_FAILURE(RHI.CreateCommandBuffer(*Frame.CommandAllocator, Frame.CommandBuffer))
    }
}

void RHIDestoryQueuedFrames(RHIContext const& Context) {
    RHIInterface& RHI{Context.getRhi()};

    for (RHIQueuedFrame& QueuedFrame : Context.getQueuedFrames()) {
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
    RHI_ABORT_ON_FAILURE(Context.getRhi().GetQueue(*Context.getDevice(), nri::QueueType::GRAPHICS, 0, Context.getGraphicsQueue()))
}

} // namespace

RHIContext::RHIContext(nri::GraphicsAPI const Backend)
    : backend_(Backend),
      rhi_(makeUnique<RHIInterface>()),
      resources_(makeUnique<RHIContextResources>()) {
}

void RHIContext::initialize() {
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

void RHIContext::shutdown() {
    rhi_->DeviceWaitIdle(getDevice());

    // Destroy all owned resources.
    RHIDestoryQueuedFrames(*this);
    RHIDestroyStreamer(*this);
    RHIDestroyFrameFence(*this);
    RHIDestoryDevice(*this);
}

void RHIContext::waitIdle() {
    if (rhi_) {
        rhi_->DeviceWaitIdle(getDevice());
    }
}

} // namespace px

// NOLINTEND
