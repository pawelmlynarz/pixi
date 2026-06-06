// © 2026 Pawel Mlynarz

#include "imgui/imgui_draw_utils.h"

#if WITH_IMGUI

#include "imgui.h"
#include "imgui_internal.h"

namespace px::imgui {

void DrawDashedLine(
    ImDrawList* const DrawList, ImVec2 const& A, ImVec2 const& B, ImU32 const Color,
    float const DashLength, float const GapLength, float const Thickness
) {
    ImVec2 Dir{ImVec2(B.x - A.x, B.y - A.y)};
    float const Length{sqrtf(Dir.x * Dir.x + Dir.y * Dir.y)};

    if (Length <= 0.0f) {
        return;
    }

    Dir.x /= Length;
    Dir.y /= Length;

    float Pos{0.0f};
    bool Draw{true};

    while (Pos < Length) {
        float const Seg{Draw ? DashLength : GapLength};
        float End{Pos + Seg};

        End = std::min(End, Length);

        if (Draw) {
            ImVec2 const p1{ImVec2(A.x + Dir.x * Pos, A.y + Dir.y * Pos)};
            ImVec2 const p2{ImVec2(A.x + Dir.x * End, A.y + Dir.y * End)};
            DrawList->AddLine(p1, p2, Color, Thickness);
        }

        Pos = End;
        Draw = !Draw;
    }
}

void DrawDashedRect(
    ImDrawList* const DrawList, ImVec2 const& Min, ImVec2 const& Max, ImU32 const Color,
    float const DashLength, float const GapLength, float const Thickness
) {
    DrawDashedLine(DrawList, ImVec2(Min.x, Min.y), ImVec2(Max.x, Min.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Max.x, Min.y), ImVec2(Max.x, Max.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Max.x, Max.y), ImVec2(Min.x, Max.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Min.x, Max.y), ImVec2(Min.x, Min.y), Color, DashLength, GapLength, Thickness);
}

void DrawDashedWindowBorder(
    ImVec2 const& Padding, ImColor const Color, float const DashLength, float const GapLength, float const Thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y + ImGui::GetWindowSize().y)};

    p0.x += Padding.x;
    p0.y += Padding.y;
    p1.x -= Padding.x;
    p1.y -= Padding.y;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};

    DrawDashedRect(
        dl, p0, p1, Color, DashLength, GapLength, Thickness
    );
}

void DrawDashedHeader(
    char const* const Text, ImVec2 const& Padding, ImColor const LineColor, ImColor const TextColor, 
    float const DashLength, float const GapLength, float const Thickness, float TextPaddingLeft
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y)};

    p0.x += Padding.x;
    p1.x -= Padding.x;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};
    ImVec2 const TextSize{ImGui::CalcTextSize(Text)};

    float constexpr Spacing{8.0f};
    float const y{p0.y + Padding.y};

    float const TextX{ImMax(p0.x + TextPaddingLeft, p0.x)};
    float const TextEnd{TextX + TextSize.x};

    float const LeftLineEnd{ImClamp(TextX - Spacing, p0.x, p1.x)};
    float const RightLineStart{ImClamp(TextEnd + Spacing, p0.x, p1.x)};

    DrawDashedLine(dl, ImVec2(p0.x, y), ImVec2(LeftLineEnd, y), LineColor, DashLength, GapLength, Thickness);

    dl->AddText(
        ImVec2(TextX, y - TextSize.y * 0.5f), TextColor, Text
    );

    DrawDashedLine(
        dl, ImVec2(RightLineStart, y), ImVec2(p1.x, y), LineColor, DashLength, GapLength, Thickness
    );
}

} // namespace px::imgui

#endif
