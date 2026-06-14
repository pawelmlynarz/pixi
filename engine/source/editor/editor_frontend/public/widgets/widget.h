// © 2026 Pawel Mlynarz

#pragma once

#include "frontend_module.h"
#include "core_minimal.h"

#include <string_view>

namespace px {

using ImWidgetId = std::string_view;

constexpr char const* CStr(ImWidgetId const WidgetId) {
    return WidgetId.data();
}

/**
 * Base class for container widgets (windows / panels).
 */
class ImContainerWidget {
  public:
    explicit ImContainerWidget(ImWidgetId StrId) : StrId_(StrId) {}
    virtual ~ImContainerWidget() = default;

    ImWidgetId GetId() const { return StrId_; }

    virtual void Draw() = 0;

  private:
    ImWidgetId StrId_{};
};

/**
 * Base class for simple widgets (control widgets, labels, images)
 */
template <typename TConfig>
class ImWidgetWithConfig {
  public:
    explicit ImWidgetWithConfig(TConfig const& Config) : Config_(Config) {}
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

    virtual ImVec2 ComputeExtent() const = 0;

    virtual void DrawInExtent(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent) const = 0;
};

} // namespace px
