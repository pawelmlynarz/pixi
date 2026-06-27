// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// pxfrontend
#include "window/window.h"

namespace px {

class ImContainerWidget;

namespace ed {

class EditorMainFrameWindow final : public Window {
  public:
    PXEDITOR_FRONTEND_API EditorMainFrameWindow();
    PXEDITOR_FRONTEND_API ~EditorMainFrameWindow() override;

  protected:
    void drawImGui() override;

  private:
    using WidgetsList = std::vector<std::unique_ptr<ImContainerWidget>>;

    WidgetsList widgets_;
};

} // namespace ed

} // namespace px
