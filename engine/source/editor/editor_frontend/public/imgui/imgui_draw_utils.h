// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"
#include "imgui.h"

namespace px::edimgui {

/**
 * Draws dashed line.
 */
PXEDITOR_FRONTEND_API void DrawDashedLine(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

/**
 * Draws dashed rectangle (4 dashed lines).
 */
PXEDITOR_FRONTEND_API void DrawDashedRect(
    ImDrawList* DrawList, ImVec2 const& Min, ImVec2 const& Max, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

/**
 * Draws dashed window border with configurable padding.
 */
PXEDITOR_FRONTEND_API void DrawDashedWindowBorder(
    ImVec2 const& Padding = {6.f, 6.f},
    ImColor Color = IM_COL32(160, 160, 160, 180),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

/**
 * Draws Simple header with text. Use ImEditorPanelHeader if you to embed widgets inside it.
 * -- [Header Text] ------------------------------------------------------------------
 */
PXEDITOR_FRONTEND_API void DrawDashedHeader(
    char const* Text, ImVec2 const& Padding = {6.f, 6.f}, float TextPaddingLeft = 0.0f,
    ImColor LineColor = IM_COL32(160, 160, 160, 180), ImColor TextColor = IM_COL32(220, 220, 220, 255),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

/**
 * Draws dashed line with precomputed gaps. Use to embed widgets inside the header dashed line.
 * -- [Widget A] --[Widget B]---------------------------------------------[Widget C]---
 */
PXEDITOR_FRONTEND_API void DrawDashedLineWithGaps(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B, std::vector<ImVec2> const& Gaps,
    ImColor LineColor = IM_COL32(160, 160, 160, 180), float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

enum class EImGuiFontSize : uint8 {
    Small,
    Medium,
    Large,
    Max
};

/**
 * Pushes engine font of a predefined size for text rendering.
 */
PXEDITOR_FRONTEND_API void PushFont(EImGuiFontSize FontSize);

/**
 * Pops engine font.
 */
PXEDITOR_FRONTEND_API void PopFont();

/**
 * Same as ImGui::BeginChild, but adds additional padding for the child window from the parent borders.
 */
PXEDITOR_FRONTEND_API bool BeginChildPadded(char const* StrId, ImVec2 const& Size = ImVec2(0, 0), ImVec2 const& Padding = ImVec2(0, 0), ImGuiChildFlags ChildFlags = 0, ImGuiWindowFlags WindowFlags = 0);

/**
 * Button that has no background and an underline.
 */
PXEDITOR_FRONTEND_API bool UnderlineButton(
    char const* Label,
    ImColor Color = IM_COL32(200, 200, 200, 255), ImColor HoveredColor = IM_COL32(220, 220, 220, 255), ImColor PressedColor = IM_COL32(200, 200, 200, 255)
);

} // namespace px::edimgui
