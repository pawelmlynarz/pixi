// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

namespace px::ed {

class ImViewport : public ImEditorPanel {
  public:
    void Draw() override;
};

} // namespace px::ed
