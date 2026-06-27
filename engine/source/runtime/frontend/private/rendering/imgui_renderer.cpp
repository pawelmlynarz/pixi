// © 2026 Pawel Mlynarz

#include "rendering/imgui_renderer.h"

#if WITH_IMGUI

// pxrhi
#include "rhi_asserts.h"

// imgui
#include "imgui.h"

namespace px {

void ImGuiRenderer::initialize(nri::Device* const device, UVector2 const& displaySize) {
    device_ = device;
    pxAssert(device_);

    IMGUI_CHECKVERSION();
    displaySize_ = displaySize;
    imguiContext_ = ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiStyle& style{ImGui::GetStyle()};
    style.FrameBorderSize = 1;
    style.WindowBorderSize = 1;

    ImGuiIO& io{ImGui::GetIO()};
    io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    io.BackendFlags |= ImGuiBackendFlags_RendererHasTextures;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;
    io.DisplaySize = ImVec2(static_cast<float>(displaySize_.x), static_cast<float>(displaySize_.y));

    ImFontConfig fontConfig{};
    fontConfig.SizePixels = 13.f;

    io.Fonts->AddFontDefaultVector(&fontConfig);

    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*device_, NRI_INTERFACE(nri::ImguiInterface), &imguiInterface_))

    nri::ImguiDesc constexpr imguiDesc{};
    RHI_ABORT_ON_FAILURE(imguiInterface_.CreateImgui(*device_, imguiDesc, imguiRenderer_))
}

void ImGuiRenderer::shutdown() {
    if (!hasUserInterface()) {
        return;
    }

    imguiInterface_.DestroyImgui(imguiRenderer_);
    ImGui::DestroyContext();

    imguiRenderer_ = nullptr;
}

// NOLINTNEXTLINE(readability-make-member-function-const)
void ImGuiRenderer::tick([[maybe_unused]] float const dt) {}

void ImGuiRenderer::cmdCopyImguiData(nri::CommandBuffer& cmdBuffer, nri::Streamer& streamer) const {
    if (!hasUserInterface()) {
        return;
    }

    ImDrawData const& drawData{*ImGui::GetDrawData()};

    nri::CopyImguiDataDesc const copyImguiDataDesc{
        .drawLists = drawData.CmdLists.Data,
        .drawListNum = static_cast<uint32>(drawData.CmdLists.Size),
        .textures = drawData.Textures->Data,
        .textureNum = static_cast<uint32>(drawData.Textures->Size)
    };

    imguiInterface_.CmdCopyImguiData(cmdBuffer, streamer, *imguiRenderer_, copyImguiDataDesc);
}

void ImGuiRenderer::cmdDrawImgui(nri::CommandBuffer& cmdBuffer, nri::Format const attachmentFormat, float const sdrScale, bool const bIsSrgb) const {
    if (!hasUserInterface()) {
        return;
    }

    ImDrawData const& drawData{*ImGui::GetDrawData()};

    nri::DrawImguiDesc const drawImguiDesc{
        .drawLists = drawData.CmdLists.Data,
        .drawListNum = static_cast<uint32>(drawData.CmdLists.Size),
        .displaySize = {.w = static_cast<nri::Dim_t>(drawData.DisplaySize.x), .h = static_cast<nri::Dim_t>(drawData.DisplaySize.y)},
        .hdrScale = sdrScale,
        .attachmentFormat = attachmentFormat,
        .linearColor = !bIsSrgb
    };

    imguiInterface_.CmdDrawImgui(cmdBuffer, *imguiRenderer_, drawImguiDesc);
}

void* ImGuiRenderer::getImguiContext() {
    return imguiContext_;
}

void ImGuiRenderer::requestResizeDisplaySize(UVector2 const& displaySize) {
    displaySize_ = displaySize;

    ImGuiIO& io{ImGui::GetIO()};
    io.DisplaySize = ImVec2(static_cast<float>(displaySize_.x), static_cast<float>(displaySize_.y));
}

} // namespace px

#endif
