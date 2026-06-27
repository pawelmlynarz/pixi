// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

namespace px::ed {

class ImHeader : public ImPanel {
  public:
    using ImPanel::ImPanel;

  protected:
    void drawPanelContent() override;
};

} // namespace px::ed
