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
PXEDITOR_FRONTEND_API void DrawDashedLine(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

/**
 * Draws dashed rectangle (4 dashed lines).
 */
PXEDITOR_FRONTEND_API void DrawDashedRect(
    ImDrawList* DrawList, ImVec2 const& Min, ImVec2 const& Max,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

/**
 * Draws dashed window border with configurable padding.
 */
PXEDITOR_FRONTEND_API void DrawDashedWindowBorder(
    ImVec2 const& Padding = {6.f, 6.f},
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

/**
 * Draws Simple header with text. Use ImEditorPanelHeader if you to embed widgets inside it.
 * -- [Header Text] ------------------------------------------------------------------
 */
PXEDITOR_FRONTEND_API void DrawDashedHeader(
    char const* Text, ImVec2 const& Padding = {6.f, 6.f}, float TextPaddingLeft = 0.0f,
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

/**
 * Draws dashed line with precomputed gaps. Use to embed widgets inside the header dashed line.
 * -- [Widget A] --[Widget B]---------------------------------------------[Widget C]---
 */
PXEDITOR_FRONTEND_API void DrawDashedLineWithGaps(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B, std::vector<ImVec2> const& Gaps,
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

} // namespace px::ed
