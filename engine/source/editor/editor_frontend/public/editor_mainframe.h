// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// pxfrontend
#include "widgets/swindow.h"

namespace px {

class ImContainerWidget;

namespace ed {

class SEditorMainFrame final : public SWindow {
  public:
    PXEDITOR_FRONTEND_API SEditorMainFrame();
    PXEDITOR_FRONTEND_API ~SEditorMainFrame() override;

  protected:
    void drawImGui() override;

  private:
    std::vector<std::unique_ptr<ImContainerWidget>> widgets_;
};

} // namespace ed

} // namespace px
