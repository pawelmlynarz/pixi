// © 2026 Pawel Mlynarz

#include "widgets/panels/scene_hierarchy.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

namespace px::ed {

void ImSceneHierarchy::DrawPanelContent() {
    DrawDashedWindowBorder();
    PushFont(EImFontSize::Large);
    DrawDashedHeader("[SCENE HIERARCHY]", {24.f, 24.f}, 25);
    PopFont();
};

} // namespace px::ed
