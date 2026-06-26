// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

namespace px::ed {

class ImAssetBrowser : public ImPanel {
    using ImPanel::ImPanel;

  protected:
    void drawPanelContent() override;
};

} // namespace px::ed
