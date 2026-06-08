// © 2026 Pawel Mlynarz

#pragma once

#if WITH_IMGUI

#include "frontend_module.h"
#include "imgui.h"

namespace px::imgui {

PXFRONTEND_API void DrawDashedLine(
    ImDrawList* DrawList, ImVec2 const& A, ImVec2 const& B, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

PXFRONTEND_API void DrawDashedRect(
    ImDrawList* DrawList, ImVec2 const& Min, ImVec2 const& Max, ImU32 Color,
    float DashLength = 6.0f, float GapLength = 4.0f, float Thickness = 2.f
);

PXFRONTEND_API void DrawDashedWindowBorder(
    ImVec2 const& Padding = {6.f, 6.f},
    ImColor Color = IM_COL32(160, 160, 160, 180),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

PXFRONTEND_API void DrawDashedHeader(
    char const* Text, ImVec2 const& Padding = {6.f, 6.f}, float TextPaddingLeft = 0.0f,
    ImColor LineColor = IM_COL32(160, 160, 160, 180), ImColor TextColor = IM_COL32(220, 220, 220, 255),
    float DashLength = 10.0f, float GapLength = 2.0f, float Thickness = 2.f
);

enum class EImGuiFontSize : uint8 {
    Small,
    Medium,
    Large,
    Max
};

PXFRONTEND_API void PushFont(EImGuiFontSize FontSize);
PXFRONTEND_API void PopFont();

} // namespace px::imgui

#endif
