// © 2026 Pawel Mlynarz

#include "panels/asset_browser.h"
#include "editor_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

namespace px::ed {

void ImAssetBrowser::Draw() {
    ImGui::Begin(NameAssetBrowser, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();
        edimgui::PushFont(edimgui::EImGuiFontSize::Large);
        edimgui::DrawDashedHeader("[ASSET BROWSER]", {24.f, 24.f}, 25);
        edimgui::PopFont();
    }
    ImGui::End();
};

} // namespace px::ed
