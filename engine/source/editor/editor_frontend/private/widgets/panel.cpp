//// © 2026 Pawel Mlynarz

#include "widgets/panel.h"

namespace px::ed {

namespace {

constexpr ImGuiWindowFlags getDefaultPanelFlags() {
    ImGuiWindowFlags constexpr windowFlags{
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus
    };
    return windowFlags;
}

} // namespace

void ImPanel::draw() {
    ImGui::Begin(cStr(getId()), nullptr, getDefaultPanelFlags());
    drawPanelContent();
    ImGui::End();
}

} // namespace px::ed
