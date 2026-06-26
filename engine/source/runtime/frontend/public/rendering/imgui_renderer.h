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
    void initialize(nri::Device* device);

    void shutdown();

    void tick(float dt);

    inline bool hasUserInterface() const;

    PXFRONTEND_API void cmdCopyImguiData(nri::CommandBuffer& cmdBuffer, nri::Streamer& streamer) const;

    PXFRONTEND_API void cmdDrawImgui(nri::CommandBuffer& cmdBuffer, nri::Format attachmentFormat, float sdrScale, bool bIsSrgb) const;

    PXFRONTEND_API void* getImguiContext();

  private:
    void* imguiContext_{nullptr};
    nri::Device* device_{nullptr};
    nri::Imgui* imguiRenderer_{nullptr};
    nri::ImguiInterface imguiInterface_{};
};

inline bool ImGuiRenderer::hasUserInterface() const {
    return imguiRenderer_ != nullptr;
}

} // namespace px

#endif
