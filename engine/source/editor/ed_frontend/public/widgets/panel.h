// © 2026 Pawel Mlynarz

#pragma once

#include "widget.h"

namespace px::ed {

class ImPanel : public ImContainerWidget {
  public:
    using ImContainerWidget::ImContainerWidget;

    void draw() override;

  protected:
    virtual void drawPanelContent() {};
};

} // namespace px::ed
