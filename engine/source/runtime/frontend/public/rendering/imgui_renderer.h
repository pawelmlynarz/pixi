// © 2026 Pawel Mlynarz

#pragma once

#if WITH_IMGUI

#include "frontend_module.h"

// NRI
#include "NRI.h"
#include "Extensions/NRIImgui.h"
#include "tools/misc.h"

namespace px {

class ImGuiRenderer : NonCopyableNonMovable {
  public:
    void Initialize(nri::Device* Device);

    void Shutdown();

    void Tick(float Dt);

    inline bool HasUserInterface() const;

    PXFRONTEND_API void CmdCopyImguiData(nri::CommandBuffer& CmdBuffer, nri::Streamer& Streamer) const;

    PXFRONTEND_API void CmdDrawImgui(nri::CommandBuffer& CmdBuffer, nri::Format AttachmentFormat, float SdrScale, bool bIsSrgb) const;

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
