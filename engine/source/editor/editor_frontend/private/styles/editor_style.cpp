// © 2026 Pawel Mlynarz

#include "styles/editor_style.h"

// imgui
#include "imgui_internal.h"

#include <optional>

namespace px::ed {

namespace {

std::optional<StyleConfig> CurrentStyle;

} // namespace

StyleConfig::StyleConfig()
    : NativeColors(ImGui::GetStyle().Colors) {
}

ImVec4& StyleConfig::operator[](int const Idx) {
    if (Idx < ImGuiCol_COUNT) {
        Assert(NativeColors.data());
        return NativeColors[Idx];
    }
    return PxColors[Idx - ImGuiCol_COUNT];
}

ImVec4 const& StyleConfig::operator[](int const Idx) const {
    return const_cast<StyleConfig*>(this)->operator[](Idx);
}

StyleConfig& EdStyle::GetStyle() {
    Assert(CurrentStyle.has_value());
    return *CurrentStyle;
}

ImU32 EdStyle::GetColorU32(ImGuiCol const Idx, float const AlphaMul) {
    StyleConfig const& Style{GetStyle()};

    ImVec4 Color{Style[Idx]};
    Color.w *= GImGui->Style.Alpha * AlphaMul;

    return ImGui::ColorConvertFloat4ToU32(Color);
}

void EdStyle::SetDefaultStyle() {
    StyleConfig DefaultConfig;

    DefaultConfig[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    DefaultConfig[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    DefaultConfig[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    DefaultConfig[ImGuiCol_Border] = ImVec4{0.f, 0., 0., 0.};
    DefaultConfig[ImGuiCol_Text] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    DefaultConfig[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 1.f);

    DefaultConfig[ImGuiCol_ResizeGrip] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.15f);
    DefaultConfig[ImGuiCol_ResizeGripHovered] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.3f);
    DefaultConfig[ImGuiCol_ResizeGripActive] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.3f);

    DefaultConfig[PxGuiCol_Text] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    DefaultConfig[PxGuiCol_TextActive] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    DefaultConfig[PxGuiCol_TextHovered] = ImVec4{0.8627f, 0.8627f, 0.8627f, 1.0f};
    DefaultConfig[PxGuiCol_DashedFrameBorder] = ImVec4{0.627451f, 0.627451f, 0.627451f, 0.7f};
    DefaultConfig[PxGuiCol_FrameBorder] = ImVec4{0.427451f, 0.427451f, 0.427451f, 0.55f};

    CurrentStyle = DefaultConfig;
}

} // namespace px::ed
