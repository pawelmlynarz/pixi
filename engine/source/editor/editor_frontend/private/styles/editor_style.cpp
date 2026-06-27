// © 2026 Pawel Mlynarz

#include "styles/editor_style.h"

// imgui
#include "imgui_internal.h"

#include <optional>

namespace px::ed {

namespace {

std::optional<StyleConfig> currentStyle;

} // namespace

StyleConfig::StyleConfig()
    : nativeColors_(ImGui::GetStyle().Colors) {
}

ImVec4& StyleConfig::operator[](int const idx) {
    if (idx < ImGuiCol_COUNT) {
        pxAssert(nativeColors_.data());
        return nativeColors_[idx];
    }
    return pxColors_[idx - ImGuiCol_COUNT];
}

ImVec4 const& StyleConfig::operator[](int const idx) const {
    return const_cast<StyleConfig*>(this)->operator[](idx);
}

StyleConfig& EdStyle::getStyle() {
    pxAssert(currentStyle.has_value());
    return *currentStyle;
}

ImU32 EdStyle::getColorU32(ImGuiCol const idx, float const alphaMul) {
    StyleConfig const& style{getStyle()};

    ImVec4 color{style[idx]};
    color.w *= GImGui->Style.Alpha * alphaMul;

    return ImGui::ColorConvertFloat4ToU32(color);
}

void EdStyle::setDefaultStyle() {
    StyleConfig defaultConfig;

    defaultConfig[ImGuiCol_FrameBg] = ImVec4{0.2f, 0.205f, 0.21f, 1.0f};
    defaultConfig[ImGuiCol_FrameBgHovered] = ImVec4{0.3f, 0.305f, 0.31f, 1.0f};
    defaultConfig[ImGuiCol_FrameBgActive] = ImVec4{0.15f, 0.1505f, 0.151f, 1.0f};
    defaultConfig[ImGuiCol_Border] = ImVec4{0.f, 0., 0., 0.};
    defaultConfig[ImGuiCol_Text] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    defaultConfig[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 1.f);

    defaultConfig[ImGuiCol_ResizeGrip] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.15f);
    defaultConfig[ImGuiCol_ResizeGripHovered] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.3f);
    defaultConfig[ImGuiCol_ResizeGripActive] = ImVec4(0.627451f, 0.627451f, 0.627451f, 0.3f);

    defaultConfig[PxGuiCol_Text] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    defaultConfig[PxGuiCol_TextActive] = ImVec4{0.7843f, 0.7843f, 0.7843f, 1.0f};
    defaultConfig[PxGuiCol_TextHovered] = ImVec4{0.8627f, 0.8627f, 0.8627f, 1.0f};
    defaultConfig[PxGuiCol_DashedFrameBorder] = ImVec4{0.627451f, 0.627451f, 0.627451f, 0.7f};
    defaultConfig[PxGuiCol_FrameBorder] = ImVec4{0.427451f, 0.427451f, 0.427451f, 0.55f};

    currentStyle = defaultConfig;
}

} // namespace px::ed
