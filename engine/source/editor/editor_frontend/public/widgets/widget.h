// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

// imgui
#include "imgui.h"

#include <string_view>

namespace px {

using ImWidgetId = std::string_view;

constexpr char const* cStr(ImWidgetId const widgetId) {
    return widgetId.data();
}

/**
 * Base class for container widgets (windows / panels).
 */
class ImContainerWidget {
  public:
    explicit ImContainerWidget(ImWidgetId strId) : strId_(strId) {}
    virtual ~ImContainerWidget() = default;

    ImWidgetId getId() const { return strId_; }

    virtual void draw() = 0;

  private:
    ImWidgetId strId_{};
};

/**
 * Base class for simple widgets (control widgets, labels, images)
 */
template <typename TConfig>
class ImWidgetWithConfig {
  public:
    explicit ImWidgetWithConfig(TConfig config) : Config_(std::move(config)) {}
    virtual ~ImWidgetWithConfig() = default;

  protected:
    TConfig Config_;
};

/**
 * An interface for widgets that needs to precompute their extent before being drawn to the screen.
 */
class IPrecomputedExtentWidget {
  public:
    virtual ~IPrecomputedExtentWidget() = default;

    virtual ImVec2 computeExtent() const = 0;

    virtual void drawInExtent(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent) const = 0;
};

} // namespace px
