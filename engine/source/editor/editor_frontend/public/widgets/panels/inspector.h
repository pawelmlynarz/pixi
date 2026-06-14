// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

namespace px::ed {

class ImInspector : public ImPanel {
  public:
    using ImPanel::ImPanel;

  protected:
    void DrawPanelContent() override;
};

} // namespace px::ed
