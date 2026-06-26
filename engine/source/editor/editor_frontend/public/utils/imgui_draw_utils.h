// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"

// imgui
#include "imgui.h"

#include <vector>

namespace px::ed {

/**
 * Draws dashed line.
 */
PXEDITOR_FRONTEND_API void drawDashedLine(
    ImDrawList* drawList, ImVec2 const& a, ImVec2 const& b,
    float dashLength = 6.0f, float gapLength = 4.0f, float thickness = 2.f
);

/**
 * Draws dashed rectangle (4 dashed lines).
 */
PXEDITOR_FRONTEND_API void drawDashedRect(
    ImDrawList* drawList, ImVec2 const& min, ImVec2 const& max,
    float dashLength = 6.0f, float gapLength = 4.0f, float thickness = 2.f
);

/**
 * Draws dashed window border with configurable padding.
 */
PXEDITOR_FRONTEND_API void drawDashedWindowBorder(
    ImVec2 const& padding = {6.f, 6.f},
    float dashLength = 10.0f, float gapLength = 2.0f, float thickness = 2.f
);

/**
 * Draws Simple header with text. Use ImEditorPanelHeader if you to embed widgets inside it.
 * -- [Header Text] ------------------------------------------------------------------
 */
PXEDITOR_FRONTEND_API void drawDashedHeader(
    char const* text, ImVec2 const& padding = {6.f, 6.f}, float textPaddingLeft = 0.0f,
    float dashLength = 10.0f, float gapLength = 2.0f, float thickness = 2.f
);

/**
 * Draws dashed line with precomputed gaps. Use to embed widgets inside the header dashed line.
 * -- [Widget A] --[Widget B]---------------------------------------------[Widget C]---
 */
PXEDITOR_FRONTEND_API void drawDashedLineWithGaps(
    ImDrawList* drawList, ImVec2 const& a, ImVec2 const& b, std::vector<ImVec2> const& gaps,
    float dashLength = 10.0f, float gapLength = 2.0f, float thickness = 2.f
);

} // namespace px::ed
