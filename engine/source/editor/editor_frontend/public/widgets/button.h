// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "common/callbacks.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_widget.h"

namespace px::ed {

struct ImButtonConfig {
    std::string_view Text{"Button"};
    edimgui::EImGuiFontSize FontSize{edimgui::EImGuiFontSize::Medium};
    
    bool bUnderline{false};

    ButtonPressedCallback OnPressed;
};

class ImButton : public ImPrecomputedExtentWidget {
  public:
    ImButton(ImButtonConfig const& Config);

    // ~ImPrecomputedExtentWidget Begin

    ImVec2 ComputeExtent() const override;
    void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const override;

    // ~ImPrecomputedExtentWidget End

  private:
    ImButtonConfig Config_;
};

} // namespace px::ed
