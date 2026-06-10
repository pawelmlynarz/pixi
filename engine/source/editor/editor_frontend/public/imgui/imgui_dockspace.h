// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// imgui
#include "imgui.h"

namespace px::edimgui {

struct ImGuiDockSpaceConfig {
    std::string_view Name{"DockSpace"};

    float WindowRounding{0.0f};
    float WindowBorderSize{0.0f};
    ImVec2 WindowPadding{ImVec2(0.0f, 0.0f)};

    ImGuiDockNodeFlags DockSpaceFlags{};
    ImGuiWindowFlags HostWindowFlags{};

    std::function<void(ImGuiViewport*, ImGuiID)> BuildDockSpaceLayoutStrategy;
};

class ImGuiDockSpace {
  public:
    PXEDITOR_FRONTEND_API ImGuiDockSpace(ImGuiViewport* Viewport, ImGuiDockSpaceConfig const& Config);

  private:
    ImGuiID DockSpaceID_;
    ImGuiViewport* Viewport_{nullptr};
    ImGuiDockSpaceConfig Config_;
};

} // namespace px::edimgui
