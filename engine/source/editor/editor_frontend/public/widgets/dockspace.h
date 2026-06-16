// © 2026 Pawel Mlynarz

#pragma once

// imgui
#include "imgui.h"

namespace px::ed {

struct ImDockSpaceConfig {
    std::string_view Name{"DockSpace"};

    float WindowRounding{0.0f};
    float WindowBorderSize{0.0f};
    ImVec2 WindowPadding{ImVec2(0.0f, 0.0f)};

    ImGuiDockNodeFlags DockSpaceFlags{};
    ImGuiWindowFlags HostWindowFlags{};

    std::function<void(ImGuiViewport*, ImGuiID)> BuildDockSpaceLayoutStrategy;
};

class ImDockSpace {
  public:
    ImDockSpace(ImGuiViewport* Viewport, ImDockSpaceConfig const& Config);

  private:
    ImGuiID DockSpaceID_;
    ImGuiViewport* Viewport_{nullptr};
    ImDockSpaceConfig Config_;
};

} // namespace px::ed
