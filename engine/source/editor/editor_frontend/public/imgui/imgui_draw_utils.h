// © 2026 Pawel Mlynarz

#pragma once

#include "editor_frontend_module.h"
#include "imgui.h"

namespace px::edimgui {

PXEDITOR_FRONTEND_API void DrawDashedLine(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

PXEDITOR_FRONTEND_API void DrawDashedRect(
    ImDrawList* DrawList, ImVec2 const& Min, ImVec2 const& Max, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

PXEDITOR_FRONTEND_API void DrawDashedWindowBorder(
    ImVec2 const& Padding = {6.f, 6.f},
    ImColor Color = IM_COL32(160, 160, 160, 180),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

PXEDITOR_FRONTEND_API void DrawDashedHeader(
    char const* Text, ImVec2 const& Padding = {6.f, 6.f}, float TextPaddingLeft = 0.0f,
    ImColor LineColor = IM_COL32(160, 160, 160, 180), ImColor TextColor = IM_COL32(220, 220, 220, 255),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

PXEDITOR_FRONTEND_API void DrawDashedLineWithGaps(
    ImDrawList* DrawList, ImVec2 A, ImVec2 B,
    ImU32 Color, float DashLen, float GapLen, float Thickness, std::vector<ImVec2> const& Gaps
);

enum class EImGuiFontSize : uint8 {
    Small,
    Medium,
    Large,
    Max
};

PXEDITOR_FRONTEND_API void PushFont(EImGuiFontSize FontSize);
PXEDITOR_FRONTEND_API void PopFont();

PXEDITOR_FRONTEND_API bool BeginChildPadded(char const* StrId, ImVec2 const& Size = ImVec2(0, 0), ImVec2 const& Padding = ImVec2(0, 0), ImGuiChildFlags ChildFlags = 0, ImGuiWindowFlags WindowFlags = 0);

} // namespace px::edimgui
