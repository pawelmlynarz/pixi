// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// imgui
#include "imgui.h"

#include <string_view>
#include <functional>

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
    ImDockSpace(ImGuiViewport* viewport, ImDockSpaceConfig const& config);

  private:
    ImGuiID dockSpaceId_;
    ImGuiViewport* viewport_{nullptr};
    ImDockSpaceConfig config_;
};

} // namespace px::ed
