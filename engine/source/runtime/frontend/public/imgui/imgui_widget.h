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

class PXFRONTEND_API ImPrecomputedExtentWidget {
  public:
    virtual ~ImPrecomputedExtentWidget() = default;

    virtual ImVec2 ComputeExtent() const = 0;

    virtual void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const = 0;
};

} // namespace px
