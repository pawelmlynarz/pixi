// © 2026 Pawel Mlynarz

#pragma once

#include "editor_widget.h"

namespace px::ed {

class ImViewport : public ImGuiEditorWidget {
  public:
    void Draw() override;
};

} // namespace px::ed
