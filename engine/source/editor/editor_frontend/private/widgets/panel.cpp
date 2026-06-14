//// © 2026 Pawel Mlynarz

#include "widgets/panel.h"

namespace px::ed {

namespace {

constexpr ImGuiWindowFlags GetDefaultPanelFlags() {
    ImGuiWindowFlags constexpr WindowFlags{
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
    };
    return WindowFlags;
}

} // namespace

void ImPanel::Draw() {
    ImGui::Begin(CStr(GetId()), nullptr, GetDefaultPanelFlags());
    DrawPanelContent();
    ImGui::End();
}

} // namespace px::ed
