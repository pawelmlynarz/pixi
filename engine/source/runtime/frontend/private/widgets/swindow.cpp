// © 2026 Pawel Mlynarz

#include "widgets/swindow.h"
#include "app/base_application.h"
#include "rendering/renderer.h"
#include "rendering/imgui_renderer.h"

// pxcore
#include "platform/generic_platform/generic_window.h"

// pxrhi
#include "rhi.h"
#include "rhi_context.h"
#include "rhi_resources.h"

// imgui
#if WITH_IMGUI
#include "imgui.h"
#endif

namespace px {

void SWindow::paintWindow() {
    renderImGuiInternal();
    renderFrameInternal();
}

void SWindow::renderImGuiInternal() {
#if WITH_IMGUI
    ImGui::NewFrame();
    {
        drawImGui();
    }
    ImGui::EndFrame();
    ImGui::Render();
#endif
}

void SWindow::renderFrameInternal() {
    // NOLINTBEGIN
    pxToDo("Rewrite");

    RHIContext const& C{getRhiContext()};
    Renderer& R{dynamic_cast<Renderer&>(BaseApplication::get().getRenderer())};
    SharedPtr const Viewport{R.getViewportResource(sharedThis(this))};
    SharedPtr const RHISwapChain{Viewport->getSwapChain()};

    RHIInterface const& RHI{C.getRhi()};

    uint32_t const QueuedFrameIndex{frameIdx_ % C.getQueuedFrameNum()};
    RHIQueuedFrame const& QueuedFrame{C.getQueuedFrames()[QueuedFrameIndex]};

    uint32_t const RecycledSemaphoreIndex{frameIdx_ % static_cast<uint32_t>(RHISwapChain->SwapChainTexturesRHI.size())};
    nri::Fence* SwapChainAcquireSemaphore{RHISwapChain->SwapChainTexturesRHI[RecycledSemaphoreIndex].AcquireSemaphore};

    uint32_t CurrentSwapChainTextureIndex{0};
    RHI.AcquireNextTexture(*RHISwapChain->SwapChain, *SwapChainAcquireSemaphore, CurrentSwapChainTextureIndex);
    RHISwapChainTexture const& SwapChainTexture{RHISwapChain->SwapChainTexturesRHI[CurrentSwapChainTextureIndex]};

    nri::CommandBuffer* CommandBuffer{QueuedFrame.CommandBuffer};
    RHI.BeginCommandBuffer(*CommandBuffer, C.getDescriptorPool());
    {
        nri::TextureBarrierDesc TextureBarriers{};
        TextureBarriers.texture = SwapChainTexture.Texture;
        TextureBarriers.after = {.access = nri::AccessBits::COLOR_ATTACHMENT, .layout = nri::Layout::COLOR_ATTACHMENT};

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
            nri::ClearAttachmentDesc ClearDesc = {};
            ClearDesc.planes = nri::PlaneBits::COLOR;
            ClearDesc.value.color.f = {.x = 0.0f, .y = 0.0f, .z = 0.0f, .w = 1.0f};

            RHI.CmdClearAttachments(*CommandBuffer, &ClearDesc, 1, nullptr, 0);
        }
        RHI.CmdEndRendering(*CommandBuffer);

        // ImGui
#if WITH_IMGUI
        R.getImGuiRenderer().cmdCopyImguiData(*CommandBuffer, *C.getStreamer());

        RHI.CmdBeginRendering(*CommandBuffer, RenderingDesc);
        {
            R.getImGuiRenderer().cmdDrawImgui(*CommandBuffer, SwapChainTexture.AttachmentFormat, 1.0f, true);
        }
        RHI.CmdEndRendering(*CommandBuffer);
#endif

        TextureBarriers.before = TextureBarriers.after;
        TextureBarriers.after = {.access = nri::AccessBits::NONE, .layout = nri::Layout::PRESENT, .stages = nri::StageBits::NONE};

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

        RHI.QueueSubmit(*C.getGraphicsQueue(), QueueSubmitDesc);
    }
    RHI.EndStreamerFrame(*C.getStreamer());

    RHI.QueuePresent(*RHISwapChain->SwapChain, *SwapChainTexture.ReleaseSemaphore);

    {
        nri::FenceSubmitDesc SignalFence{};
        SignalFence.fence = C.getFrameFence();
        SignalFence.value = 1 + frameIdx_;

        nri::QueueSubmitDesc QueueSubmitDesc{};
        QueueSubmitDesc.signalFences = &SignalFence;
        QueueSubmitDesc.signalFenceNum = 1;

        RHI.QueueSubmit(*C.getGraphicsQueue(), QueueSubmitDesc);
    }
    // NOLINTEND
}

void SWindow::setNativeWindow(WeakPtr<GenericWindow> const& nativeWindow) {
    nativeWindow_ = nativeWindow;
}

SharedPtr<GenericWindow> SWindow::getNativeWindow() const {
    return nativeWindow_.lock();
}

void SWindow::showWindow() {
    if (!bHasEverBeenShown_) {
        BaseApplication::get().getRenderer().createViewport(sharedThis(this));
    }

    if (SharedPtr const nativeWindow{nativeWindow_.lock()}; nativeWindow != nullptr) {
        nativeWindow->show();
    }

    bHasEverBeenShown_ = true;
}

void SWindow::hideWindow() {
    if (SharedPtr const window{nativeWindow_.lock()}) {
        window->hide();
    }
}

void SWindow::destoryNativeWindow() {
    if (SharedPtr const window{nativeWindow_.lock()}) {
        window->destroyWindow();
    }
}

} // namespace px
