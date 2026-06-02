// © 2026 Pawel Mlynarz

#include "widgets/swindow.h"
#include "app/base_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

// pxcore
#include "window/generic_window.h"

// pxrhi
#include "rhi.h"
#include "rhi_context.h"
#include "rhi_resources.h"

// imgui
#if WITH_IMGUI
#include "imgui.h"
#endif

namespace px {

void SWindow::PaintWindow() {
    RenderImGui_Internal();
    RenderFrame_Internal();
}

void SWindow::RenderImGui_Internal() {
#if WITH_IMGUI
    ImGui::NewFrame();
    {
        DrawImGui();
    }
    ImGui::EndFrame();
    ImGui::Render();
#endif
}

void SWindow::RenderFrame_Internal() {
    RHIContext& C{GetRHIContext()};
    Renderer& R{dynamic_cast<Renderer&>(BaseApplication::Get().GetRenderer())};
    SharedPtr Viewport{R.GetViewportResource(SharedThis(this))};
    SharedPtr RHISwapChain{Viewport->GetSwapChain()};

    RHIInterface& RHI{C.GetRHI()};

    uint32_t QueuedFrameIndex{FrameIdx_ % C.GetQueuedFrameNum()};
    RHIQueuedFrame const& QueuedFrame{C.GetQueuedFrames()[QueuedFrameIndex]};

    uint32_t RecycledSemaphoreIndex{FrameIdx_ % (uint32_t)RHISwapChain->SwapChainTexturesRHI.size()};
    nri::Fence* SwapChainAcquireSemaphore{RHISwapChain->SwapChainTexturesRHI[RecycledSemaphoreIndex].AcquireSemaphore};

    uint32_t CurrentSwapChainTextureIndex{0};
    RHI.AcquireNextTexture(*RHISwapChain->SwapChain, *SwapChainAcquireSemaphore, CurrentSwapChainTextureIndex);
    RHISwapChainTexture const& SwapChainTexture{RHISwapChain->SwapChainTexturesRHI[CurrentSwapChainTextureIndex]};

    nri::CommandBuffer* CommandBuffer{QueuedFrame.CommandBuffer};
    RHI.BeginCommandBuffer(*CommandBuffer, C.GetDescriptorPool());
    {
        nri::TextureBarrierDesc TextureBarriers{};
        TextureBarriers.texture = SwapChainTexture.Texture;
        TextureBarriers.after = {nri::AccessBits::COLOR_ATTACHMENT, nri::Layout::COLOR_ATTACHMENT};

        nri::BarrierDesc BarrierDesc{};
        BarrierDesc.textureNum = 1;
        BarrierDesc.textures = &TextureBarriers;

        RHI.CmdBarrier(*CommandBuffer, BarrierDesc);

        nri::AttachmentDesc ColorAttachmentDesc{};
        ColorAttachmentDesc.descriptor = SwapChainTexture.ColorAttachment;

        nri::RenderingDesc RenderingDesc{};
        RenderingDesc.colorNum = 1;
        RenderingDesc.colors = &ColorAttachmentDesc;
        RenderingDesc.viewMask = 0;

        // Clear
        RHI.CmdBeginRendering(*CommandBuffer, RenderingDesc);
        {
            nri::ClearAttachmentDesc clearDesc = {};
            clearDesc.planes = nri::PlaneBits::COLOR;
            clearDesc.value.color.f = {1.0f, 1.0f, 0.0f, 1.0f};

            RHI.CmdClearAttachments(*CommandBuffer, &clearDesc, 1, nullptr, 0);
        }
        RHI.CmdEndRendering(*CommandBuffer);

        // ImGui
#if WITH_IMGUI
        R.GetImGuiRenderer().CmdCopyImguiData(*CommandBuffer, *C.GetStreamer());

        RHI.CmdBeginRendering(*CommandBuffer, RenderingDesc);
        {
            R.GetImGuiRenderer().CmdDrawImgui(*CommandBuffer, SwapChainTexture.AttachmentFormat, 1.0f, true);
        }
        RHI.CmdEndRendering(*CommandBuffer);
#endif

        TextureBarriers.before = TextureBarriers.after;
        TextureBarriers.after = {nri::AccessBits::NONE, nri::Layout::PRESENT, nri::StageBits::NONE};

        RHI.CmdBarrier(*CommandBuffer, BarrierDesc);
    }
    RHI.EndCommandBuffer(*CommandBuffer);

    { // Submit
        nri::FenceSubmitDesc TextureAcquiredFence{};
        TextureAcquiredFence.fence = SwapChainAcquireSemaphore;
        TextureAcquiredFence.stages = nri::StageBits::COLOR_ATTACHMENT;

        nri::FenceSubmitDesc RenderingFinishedFence{};
        RenderingFinishedFence.fence = SwapChainTexture.ReleaseSemaphore;

        nri::QueueSubmitDesc QueueSubmitDesc{};
        QueueSubmitDesc.waitFences = &TextureAcquiredFence;
        QueueSubmitDesc.waitFenceNum = 1;
        QueueSubmitDesc.commandBuffers = &QueuedFrame.CommandBuffer;
        QueueSubmitDesc.commandBufferNum = 1;
        QueueSubmitDesc.signalFences = &RenderingFinishedFence;
        QueueSubmitDesc.signalFenceNum = 1;

        RHI.QueueSubmit(*C.GetGraphicsQueue(), QueueSubmitDesc);
    }
    RHI.EndStreamerFrame(*C.GetStreamer());

    RHI.QueuePresent(*RHISwapChain->SwapChain, *SwapChainTexture.ReleaseSemaphore);

    {
        nri::FenceSubmitDesc SignalFence{};
        SignalFence.fence = C.GetFrameFence();
        SignalFence.value = 1 + FrameIdx_;

        nri::QueueSubmitDesc QueueSubmitDesc{};
        QueueSubmitDesc.signalFences = &SignalFence;
        QueueSubmitDesc.signalFenceNum = 1;

        RHI.QueueSubmit(*C.GetGraphicsQueue(), QueueSubmitDesc);
    }
}

void SWindow::SetNativeWindow(WeakPtr<GenericWindow> const& NativeWindow) {
    NativeWindow_ = NativeWindow;
}

SharedPtr<GenericWindow> SWindow::GetNativeWindow() const {
    return NativeWindow_.lock();
}

void SWindow::ShowWindow() {
    if (!bHasEverBeenShown_) {
        BaseApplication::Get().GetRenderer().CreateViewport(SharedThis(this));
    }

    if (SharedPtr const NativeWindow{NativeWindow_.lock()}; NativeWindow != nullptr) {
        NativeWindow->Show();
    }

    bHasEverBeenShown_ = true;
}

void SWindow::HideWindow() {
    if (SharedPtr Window{NativeWindow_.lock()}) {
        Window->Hide();
    }
}

void SWindow::DestoryNativeWindow() {
    if (SharedPtr Window{NativeWindow_.lock()}) {
        Window->DestroyWindow();
    }
}

} // namespace px
