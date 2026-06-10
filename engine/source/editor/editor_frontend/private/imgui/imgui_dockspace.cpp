// © 2026 Pawel Mlynarz

#include "imgui/imgui_dockspace.h"

#include <unordered_map>

namespace px::edimgui {

namespace {

using DockSpaceLayoutHash = size_t;
std::vector<DockSpaceLayoutHash> InitializedLayoutsList;

ImGuiID CreateDockSpace(ImGuiViewport const* const Viewport, ImGuiDockSpaceConfig const& Config) {
    ImGui::SetNextWindowPos(Viewport->WorkPos);
    ImGui::SetNextWindowSize(Viewport->WorkSize);
    ImGui::SetNextWindowViewport(Viewport->ID);

    ImGuiWindowFlags HostWindowFlags{Config.HostWindowFlags};
    ImGuiDockNodeFlags const DockSpaceFlags{Config.DockSpaceFlags};

    if (DockSpaceFlags & ImGuiDockNodeFlags_PassthruCentralNode) {
        HostWindowFlags |= ImGuiWindowFlags_NoBackground;
    }

    ImGuiID const DockSpaceID{ImGui::GetID(Config.Name.data())};

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
    ImGui::Begin("MainFrameDockSpace", nullptr, HostWindowFlags);
    {
        ImGui::DockSpace(DockSpaceID, ImVec2(0.0f, 0.0f), DockSpaceFlags, nullptr);
    }
    ImGui::End();
    ImGui::PopStyleVar(3);

    return DockSpaceID;
}

} // namespace

ImGuiDockSpace::ImGuiDockSpace(ImGuiViewport* Viewport, ImGuiDockSpaceConfig const& Config)
    : Viewport_(Viewport), Config_(Config) {
    ImGuiIO& IO{ImGui::GetIO()};
    Assert(IO.ConfigFlags & ImGuiConfigFlags_DockingEnable);

    DockSpaceID_ = CreateDockSpace(Viewport_, Config_);

    AssertMsgf(Config.BuildDockSpaceLayoutStrategy, "BuildDockSpaceLayoutStrategy must be set.");

    DockSpaceLayoutHash const NameHash{std::hash<std::string_view>{}(Config.Name)};

    if (!std::ranges::contains(InitializedLayoutsList, NameHash)) {
        Config.BuildDockSpaceLayoutStrategy(Viewport_, DockSpaceID_);
        InitializedLayoutsList.emplace_back(NameHash);
    }
}

} // namespace px::edimgui
