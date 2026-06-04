// © 2026 Pawel Mlynarz

#include "rendering/imgui_renderer.h"

#if WITH_IMGUI

// pxrhi
#include "rhi_asserts.h"

// imgui
#include "imgui.h"

namespace px {

void ImGuiRenderer::Initialize(nri::Device* const Device) {
    Device_ = Device;
    Assert(Device_);

    IMGUI_CHECKVERSION();
    ImguiContext_ = ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiStyle& Style{ImGui::GetStyle()};
    Style.FrameBorderSize = 1;
    Style.WindowBorderSize = 1;

    ImGuiIO& IO{ImGui::GetIO()};
    IO.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
    IO.BackendFlags |= ImGuiBackendFlags_RendererHasVtxOffset;
    IO.BackendFlags |= ImGuiBackendFlags_RendererHasTextures;
    IO.IniFilename = nullptr;

    ImFontConfig FontConfig{};
    FontConfig.SizePixels = 13.f;

    IO.Fonts->AddFontDefaultVector(&FontConfig);

    RHI_ABORT_ON_FAILURE(nri::nriGetInterface(*Device_, NRI_INTERFACE(nri::ImguiInterface), &ImguiInterface_))

    nri::ImguiDesc ImguiDesc{};
    RHI_ABORT_ON_FAILURE(ImguiInterface_.CreateImgui(*Device_, ImguiDesc, ImguiRenderer_))
}

void ImGuiRenderer::Shutdown() {
    if (!HasUserInterface())
        return;

    ImguiInterface_.DestroyImgui(ImguiRenderer_);
    ImGui::DestroyContext();

    ImguiRenderer_ = nullptr;
}

void ImGuiRenderer::Tick(float const Dt) {
    if (!HasUserInterface())
        return;

    PX_TODO("ImGui Display Size.");
    ImGuiIO& IO{ImGui::GetIO()};
    IO.DisplaySize = ImVec2(1920.f, 1080.f);
}

void ImGuiRenderer::CmdCopyImguiData(nri::CommandBuffer& CmdBuffer, nri::Streamer& Streamer) const {
    if (!HasUserInterface())
        return;

    ImDrawData const& DrawData{*ImGui::GetDrawData()};

    nri::CopyImguiDataDesc CopyImguiDataDesc{
        .drawLists = DrawData.CmdLists.Data,
        .drawListNum = static_cast<uint32>(DrawData.CmdLists.Size),
        .textures = DrawData.Textures->Data,
        .textureNum = static_cast<uint32>(DrawData.Textures->Size)
    };

    ImguiInterface_.CmdCopyImguiData(CmdBuffer, Streamer, *ImguiRenderer_, CopyImguiDataDesc);
}

void ImGuiRenderer::CmdDrawImgui(nri::CommandBuffer& CmdBuffer, nri::Format const AttachmentFormat, float const SdrScale, bool const bIsSrgb) const {
    if (!HasUserInterface())
        return;

    ImDrawData const& DrawData{*ImGui::GetDrawData()};

    nri::DrawImguiDesc DrawImguiDesc{
        .drawLists = DrawData.CmdLists.Data,
        .drawListNum = static_cast<uint32>(DrawData.CmdLists.Size),
        .displaySize = {.w = static_cast<nri::Dim_t>(DrawData.DisplaySize.x), .h = static_cast<nri::Dim_t>(DrawData.DisplaySize.y)},
        .hdrScale = SdrScale,
        .attachmentFormat = AttachmentFormat,
        .linearColor = !bIsSrgb
    };

    ImguiInterface_.CmdDrawImgui(CmdBuffer, *ImguiRenderer_, DrawImguiDesc);
}

void* ImGuiRenderer::GetImguiContext() {
    return ImguiContext_;
}

} // namespace px

#endif
