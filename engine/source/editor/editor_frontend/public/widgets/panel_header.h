// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"

namespace px::ed {

enum class EEditorPanelHeaderItemAlignment : uint8 {
    Left,
    Right
};

struct ImEditorPanelHeaderConfig {
    ImU32 LineColor{IM_COL32(160, 160, 160, 180)};
    ImVec2 HeaderPadding{ImVec2(24, 16.5)};

    float FirstWidgetPadding{24.f};
    float NextWidgetPadding{12.f};
    float GapExtraPadding{8.f};
    float DashLength{10.f};
    float GapLength{2.f};
    float Thickness{2.f};
};

/**
 * Class that manages constructing and drawing of a dashed header with possible embedded widgets.
 */
class ImEditorPanelHeader {
  public:
    using CalculateExtentStrategy = std::function<ImVec2()>;
    using DrawStrategy = std::function<void(ImDrawList* DrawList, ImVec2 CursorPos, ImVec2 Extent)>;

    /**
     * @brief Begins the header drawing section.
     *
     * @param Config Configuration.
     */
    void Begin(ImEditorPanelHeaderConfig const& Config);

    /**
     * @brief Adds a widget to the header. You must provide a strategy for drawing it
     *        and calculating its extent up front to align it properly.
     *
     * @param Alignment Left or Right.
     * @param CalculateExtentStrategy Calculating widget extent strategy.
     * @param DrawStrategy Drawing strategy. Supports both drawing using fixed functions as well as draw list.
     */
    void AddWidget(
        EEditorPanelHeaderItemAlignment Alignment,
        CalculateExtentStrategy const& CalculateExtentStrategy, DrawStrategy const& DrawStrategy
    );

    /**
     * @brief Ends the header drawing section.
     */
    void End() const;

  private:
    ImEditorPanelHeaderConfig Config_;

    struct StateData {
        ImVec2 OrygCursorPos_;

        float Y_{0.0f};
        float StartX_{0.f};
        float EndX_{0.f};
        float CursorXLeft_{0.f};
        float CursorXRight_{0.f};

        std::vector<ImVec2> Gaps_;
    } State_;
};

} // namespace px::ed
