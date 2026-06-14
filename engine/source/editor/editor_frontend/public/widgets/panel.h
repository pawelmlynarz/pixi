// © 2026 Pawel Mlynarz

#pragma once

#include "widget.h"

namespace px::ed {

class ImPanel : public ImContainerWidget {
  public:
    using ImContainerWidget::ImContainerWidget;

    void Draw() override;

  protected:
    virtual void DrawPanelContent() {};
};

} // namespace px::ed
