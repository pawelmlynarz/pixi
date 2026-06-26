// © 2026 Pawel Mlynarz

#include "widgets/dockspace.h"

#include <vector>
#include <algorithm>

namespace px::ed {

namespace {

using DockSpaceLayoutHash = size_t;
std::vector<DockSpaceLayoutHash> initializedLayoutsList;

ImGuiID createDockSpace(ImGuiViewport const* const viewport, ImDockSpaceConfig const& config) {
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags hostWindowFlags{config.HostWindowFlags};
    ImGuiDockNodeFlags const dockSpaceFlags{config.DockSpaceFlags};

    if (dockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        hostWindowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGuiID const dockSpaceId{ImGui::GetID(config.Name.data())};

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
    ImGui::Begin("MainFrameDockSpace", nullptr, hostWindowFlags);
    {
        ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), dockSpaceFlags, nullptr);
    }
    ImGui::End();
    ImGui::PopStyleVar(3);

    return dockSpaceId;
}

} // namespace

ImDockSpace::ImDockSpace(ImGuiViewport* viewport, ImDockSpaceConfig const& config)
    : viewport_(viewport), config_(config) {
    ImGuiIO const& io{ImGui::GetIO()};
    pxAssert(io.ConfigFlags & ImGuiConfigFlags_DockingEnable);

    dockSpaceId_ = createDockSpace(viewport_, config_);

    pxAssertMsgf(config.BuildDockSpaceLayoutStrategy, "BuildDockSpaceLayoutStrategy must be set.");

    DockSpaceLayoutHash const nameHash{std::hash<std::string_view>{}(config.Name)};

    if (!std::ranges::contains(initializedLayoutsList, nameHash)) {
        config.BuildDockSpaceLayoutStrategy(viewport_, dockSpaceId_);
        initializedLayoutsList.emplace_back(nameHash);
    }
}

} // namespace px::ed
