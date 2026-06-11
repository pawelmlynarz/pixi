// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px::ed {

enum class EEditorPanelHeaderItemAlignment : uint8 {
    Left,
    Right
};

class ImEditorPanelHeader {
  public:
    void Begin(float PaddingY);

    void AddWidget(float WidgetPadding, std::function<void()> WidgetDrawStrategy);
    
    void End(float PaddingX, ImU32 LineColor, float DashLen, float GapLen, float Thickness) const;

  private:
    std::vector<ImVec2> Gaps_;
    ImVec2 StartCursor_;
    float Y_{0.0f};
};

} // namespace px::ed
