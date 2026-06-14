// © 2026 Pawel Mlynarz

#include "widgets/panels/asset_browser.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImAssetBrowser::DrawPanelContent() {
    DrawDashedWindowBorder();
    PushFont(EImFontSize::Large);
    DrawDashedHeader("[ASSET BROWSER]", {24.f, 24.f}, 25);
    PopFont();
};

} // namespace px::ed
