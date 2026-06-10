// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"

namespace px {

class PXFRONTEND_API ImGuiWidget {
  public:
    ImGuiWidget() = default;
    virtual ~ImGuiWidget() = default;

    virtual void Draw() = 0;
};

} // namespace px
