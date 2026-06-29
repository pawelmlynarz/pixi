// © 2026 Pawel Mlynarz

#pragma once

#if WITH_IMGUI

#include "core_minimal.h"
#include "tools/misc.h"

// NRI
#include "NRI.h"
#include "Extensions/NRIImgui.h"

namespace px {

class ImGuiRenderer : NonCopyableNonMovable {
  public:
    void initialize(nri::Device* device, UVector2 const& displaySize);

    void shutdown();

    void tick(float dt);

    inline bool hasUserInterface() const;

    PXENGINE_API void cmdCopyImguiData(nri::CommandBuffer& cmdBuffer, nri::Streamer& streamer) const;

    PXENGINE_API void cmdDrawImgui(nri::CommandBuffer& cmdBuffer, nri::Format attachmentFormat, float sdrScale, bool bIsSrgb) const;

    PXENGINE_API void* getImguiContext();

    PXENGINE_API void requestResizeDisplaySize(UVector2 const& displaySize);

  private:
    void* imguiContext_{nullptr};
    nri::Device* device_{nullptr};
    nri::Imgui* imguiRenderer_{nullptr};
    nri::ImguiInterface imguiInterface_{};
    UVector2 displaySize_{};
};

inline bool ImGuiRenderer::hasUserInterface() const {
    return imguiRenderer_ != nullptr;
}

} // namespace px

#endif
