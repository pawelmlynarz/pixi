// © 2026 Pawel Mlynarz

#pragma once

// pxfrontend
#include "imgui/imgui_widget.h"

namespace px::ed {

class ImPanel : public ImGuiWidget {
  public:
    virtual void Draw() = 0;
};

} // namespace px::ed
