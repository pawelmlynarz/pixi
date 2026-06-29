// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// pxfrontend
#include "window/window.h"

namespace px {

class ImContainerWidget;

namespace ed {

class EditorMainFrameWindow final : public Window {
  public:
    PXENGINE_EDITOR_API EditorMainFrameWindow();
    PXENGINE_EDITOR_API ~EditorMainFrameWindow() override;

  protected:
    void drawImGui() override;

  private:
    using WidgetsList = std::vector<std::unique_ptr<ImContainerWidget>>;

    WidgetsList widgets_;
};

} // namespace ed

} // namespace px
