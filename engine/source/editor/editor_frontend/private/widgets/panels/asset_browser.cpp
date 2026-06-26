// © 2026 Pawel Mlynarz

#include "widgets/panels/asset_browser.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImAssetBrowser::drawPanelContent() {
    drawDashedWindowBorder();
    pushFont(EImFontSize::Large);
    drawDashedHeader("[ASSET BROWSER]", {24.f, 24.f}, 25);
    popFont();
};

} // namespace px::ed
