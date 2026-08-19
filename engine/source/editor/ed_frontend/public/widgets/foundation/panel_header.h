// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/widget.h"

namespace px {

class IPrecomputedExtentWidget;

} // namespace px

namespace px::ed {

enum class EWidgetAlignment : u8;

struct ImPanelHeaderConfig {
    ImVec2 HeaderPadding{ImVec2(24, 16.5)};

    f32 FirstWidgetPadding{24.f};
    f32 NextWidgetPadding{12.f};
    f32 GapExtraPadding{8.f};
    f32 DashLength{10.f};
    f32 GapLength{2.f};
    f32 Thickness{2.f};
};

/**
 * Class that manages constructing and drawing of a dashed header with possible embedded widgets.
 */
class ImPanelHeader : public ImWidgetWithConfig<ImPanelHeaderConfig> {
  public:
    using ImWidgetWithConfig::ImWidgetWithConfig;

    using CalculateExtentStrategy = std::function<ImVec2()>;
    using DrawStrategy = std::function<void(ImDrawList* drawList, ImVec2 cursorPos, ImVec2 extent)>;

    /**
     * @brief Begins the header drawing section.
     *
     * @param Config Configuration.
     */
    void begin();

    /**
     * @brief Adds a widget to the header.
     *
     * @param Alignment Left or Right.
     * @param Widget Widget implementing IPrecomputedExtentWidget interface.
     */
    void addWidget(
        EWidgetAlignment alignment, IPrecomputedExtentWidget const& widget
    );

    /**
     * @brief Adds a custom widget to the header. You must provide a strategy for drawing it
     *        and calculating its extent up front to align it properly.
     *
     * @param Alignment Left or Right.
     * @param CalculateExtentStrategy Calculating widget extent strategy.
     * @param DrawStrategy Drawing strategy. Supports both drawing using fixed functions as well as draw list.
     */
    void addWidget(
        EWidgetAlignment alignment,
        CalculateExtentStrategy const& calculateExtentStrategy, DrawStrategy const& drawStrategy
    );

    /**
     * @brief Ends the header drawing section.
     */
    void end() const;

  private:
    struct StateData {
        ImVec2 OrygCursorPos_;

        f32 Y_{0.0f};
        f32 StartX_{0.f};
        f32 EndX_{0.f};
        f32 CursorXLeft_{0.f};
        f32 CursorXRight_{0.f};

        std::vector<ImVec2> Gaps_;
    } state_;
};

} // namespace px::ed
