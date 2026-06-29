// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// pxfrontend
#include "widgets/swindow.h"

namespace px {

class ImContainerWidget;

namespace ed {

class SEditorMainFrame final : public SWindow {
  public:
    PXENGINE_EDITOR_API SEditorMainFrame();
    PXENGINE_EDITOR_API ~SEditorMainFrame() override;

  protected:
    void drawImGui() override;

  private:
    std::vector<std::unique_ptr<ImContainerWidget>> widgets_;
};

} // namespace ed

} // namespace px
