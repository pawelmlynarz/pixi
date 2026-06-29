// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "rhi_interface.h"

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
    static constexpr nri::VKBindingOffsets vkBindingOffsets{.sRegister = 0, .tRegister = 128, .bRegister = 32, .uRegister = 64};
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
    explicit RHIContext(nri::GraphicsAPI backend);

    void initialize();
    void shutdown();

  public:
    inline nri::GraphicsAPI getBackend() const;

    inline RHIInterface& getRhi() const;

    inline nri::Device*& getDevice() const;

    inline nri::Streamer*& getStreamer() const;

    inline nri::Queue*& getGraphicsQueue() const;

    inline nri::Fence*& getFrameFence() const;

    inline nri::DescriptorPool*& getDescriptorPool() const;

    inline std::vector<RHIQueuedFrame>& getQueuedFrames() const;

    static inline uint8 getQueuedFrameNum();

    void waitIdle();

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
    nri::GraphicsAPI backend_{nri::GraphicsAPI::NONE};

    UniquePtr<RHIInterface> rhi_{nullptr};
    UniquePtr<RHIContextResources> resources_{nullptr};
};

nri::GraphicsAPI RHIContext::getBackend() const {
    return backend_;
}

inline RHIInterface& RHIContext::getRhi() const {
    return *rhi_;
}

inline nri::Device*& RHIContext::getDevice() const {
    return resources_->Device;
}

inline uint8 RHIContext::getQueuedFrameNum() {
    return RHIStaticContext::bVSync ? 2 : 3;
}

inline nri::Streamer*& RHIContext::getStreamer() const {
    return resources_->Streamer;
}

inline nri::Queue*& RHIContext::getGraphicsQueue() const {
    return resources_->GraphicsQueue;
}

inline nri::Fence*& RHIContext::getFrameFence() const {
    return resources_->FrameFence;
}

inline nri::DescriptorPool*& RHIContext::getDescriptorPool() const {
    return resources_->DescriptorPool;
}

inline std::vector<RHIQueuedFrame>& RHIContext::getQueuedFrames() const {
    return resources_->QueuedFrames;
}

} // namespace px
