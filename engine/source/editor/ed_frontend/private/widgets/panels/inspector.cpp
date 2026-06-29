// © 2026 Pawel Mlynarz

#include "widgets/panels/inspector.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImInspector::drawPanelContent() {
    drawDashedWindowBorder();
    pushFont(EImFontSize::Large);
    drawDashedHeader("[INSPECTOR]", {24.f, 24.f}, 25);
    popFont();
};

} // namespace px::ed
