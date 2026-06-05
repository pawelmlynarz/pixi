// © 2026 Pawel Mlynarz

#pragma once

#include "rhi_interface.h"

// pxcore
#include "common/types.h"
#include "tools/utility.h"

// NRI
#include "NRI.h"
#include "Extensions/NRIDeviceCreation.h"
#include "Extensions/NRIStreamer.h"

namespace px {

struct RHIQueuedFrame {
    nri::CommandAllocator* CommandAllocator{nullptr};
    nri::CommandBuffer* CommandBuffer{nullptr};
    nri::Descriptor* ConstantBufferView{nullptr};
    nri::DescriptorSet* ConstantBufferDescriptorSet{nullptr};
    uint64 ConstantBufferViewOffset{0U};
};

struct RHIStaticContext {
    static constexpr bool bDebugApi{false};
    static constexpr bool bDebugNri{false};
    static constexpr bool bD3D11EnableCommandBufferEmulation{false};
    static constexpr bool bD3D12DisableEnhancedBarriers{false};
    static constexpr bool bVSync{false};
    static constexpr nri::VKBindingOffsets VkBindingOffsets{.sRegister = 0, .tRegister = 128, .bRegister = 32, .uRegister = 64};
};

struct RHIContextResources {
    nri::Device* Device{nullptr};
    nri::Streamer* Streamer{nullptr};
    nri::Queue* GraphicsQueue{nullptr};
    nri::Fence* FrameFence{nullptr};
    nri::DescriptorPool* DescriptorPool{nullptr};
    std::vector<RHIQueuedFrame> QueuedFrames;
};

class RHIContext {
  public:
    explicit RHIContext(nri::GraphicsAPI Backend);

    void Initialize();
    void Shutdown();

  public:
    inline nri::GraphicsAPI GetBackend() const;

    inline RHIInterface& GetRHI() const;

    inline nri::Device*& GetDevice() const;

    inline nri::Streamer*& GetStreamer() const;

    inline nri::Queue*& GetGraphicsQueue() const;

    inline nri::Fence*& GetFrameFence() const;

    inline nri::DescriptorPool*& GetDescriptorPool() const;

    inline std::vector<RHIQueuedFrame>& GetQueuedFrames() const;

    static inline uint8 GetQueuedFrameNum();

    /* temp shit code {
    nri::PipelineLayout* PipelineLayout{nullptr};
    nri::Pipeline* Pipeline{nullptr};
    nri::DescriptorPool* DescriptorPool = nullptr;
    nri::Buffer* ConstantBuffer = nullptr;
    nri::Buffer* GeometryBuffer = nullptr;
    uint64_t GeometryOffset = 0;
    std::vector<nri::Memory*> MemoryAllocations;
    // temp shit code } */

  private:
    nri::GraphicsAPI Backend_{nri::GraphicsAPI::NONE};

    UniquePtr<RHIInterface> RHI_{nullptr};
    UniquePtr<RHIContextResources> Resources_{nullptr};
};

nri::GraphicsAPI RHIContext::GetBackend() const {
    return Backend_;
}

inline RHIInterface& RHIContext::GetRHI() const {
    return *RHI_;
}

inline nri::Device*& RHIContext::GetDevice() const {
    return Resources_->Device;
}

inline uint8 RHIContext::GetQueuedFrameNum() {
    return RHIStaticContext::bVSync ? 2 : 3;
}

inline nri::Streamer*& RHIContext::GetStreamer() const {
    return Resources_->Streamer;
}

inline nri::Queue*& RHIContext::GetGraphicsQueue() const {
    return Resources_->GraphicsQueue;
}

inline nri::Fence*& RHIContext::GetFrameFence() const {
    return Resources_->FrameFence;
}

inline nri::DescriptorPool*& RHIContext::GetDescriptorPool() const {
    return Resources_->DescriptorPool;
}

inline std::vector<RHIQueuedFrame>& RHIContext::GetQueuedFrames() const {
    return Resources_->QueuedFrames;
}

} // namespace px
