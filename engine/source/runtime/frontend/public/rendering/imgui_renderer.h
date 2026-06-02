// © 2026 Pawel Mlynarz

#pragma once

#define WITH_IMGUI 1

#if WITH_IMGUI

#include "frontend_module.h"

// NRI
#include "NRI.h"
#include "Extensions/NRIImgui.h"
#include "tools/misc.h"

namespace px {

class ImGuiRenderer : NonCopyableNonMovable {
  public:
    void Initialize(nri::Device* const Device);

    void Shutdown();

    void Tick(float const Dt);

    inline bool HasUserInterface() const;

    PXFRONTEND_API void CmdCopyImguiData(nri::CommandBuffer& CmdBuffer, nri::Streamer& Streamer) const;

    PXFRONTEND_API void CmdDrawImgui(nri::CommandBuffer& CmdBuffer, nri::Format const AttachmentFormat, float const SdrScale, bool const bIsSrgb) const;

    PXFRONTEND_API void* GetImguiContext();

  private:
    void* ImguiContext_{nullptr};
    nri::Device* Device_{nullptr};
    nri::Imgui* ImguiRenderer_{nullptr};
    nri::ImguiInterface ImguiInterface_{};
};

inline bool ImGuiRenderer::HasUserInterface() const {
    return ImguiRenderer_ != nullptr;
}

} // namespace px

#endif
