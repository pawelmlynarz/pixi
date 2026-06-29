// © 2026 Pawel Mlynarz

#include "widgets/panels/scene_hierarchy.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImSceneHierarchy::drawPanelContent() {
    drawDashedWindowBorder();
    pushFont(EImFontSize::Large);
    drawDashedHeader("[SCENE HIERARCHY]", {24.f, 24.f}, 25);
    popFont();
};

} // namespace px::ed
