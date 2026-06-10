// © 2026 Pawel Mlynarz

#pragma once

#include "imgui.h"

namespace px::edimgui {

constexpr ImGuiWindowFlags GetEditorWidgetFlags() {
    ImGuiWindowFlags constexpr WindowFlags{
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
    };
    return WindowFlags;
}

} // namespace px::edimgui
