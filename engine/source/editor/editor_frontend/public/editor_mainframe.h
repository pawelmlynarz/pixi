// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// pxfrontend
#include "widgets/swindow.h"

namespace px::ed {

class SEditorMainFrame final : public SWindow {
public:
    PXEDITOR_FRONTEND_API SEditorMainFrame() = default;

protected:
    void DrawImGui() override;
};

} // namespace px::ed
