// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// pxfrontend
#include "widgets/swindow.h"

namespace px {

class ImGuiWidget;

namespace ed {

class SEditorMainFrame final : public SWindow {
  public:
    PXEDITOR_FRONTEND_API SEditorMainFrame();
    PXEDITOR_FRONTEND_API ~SEditorMainFrame() override;

  protected:
    void DrawImGui() override;

  private:
    using WidgetsVector = std::vector<std::unique_ptr<ImGuiWidget>>;
    WidgetsVector Widgets_;
};

} // namespace ed

} // namespace px
