// © 2026 Pawel Mlynarz

#include "utils/imgui_draw_utils.h"
#include "styles/editor_style.h"

// imgui
#include "imgui.h"
#include "imgui_internal.h"

namespace px::ed {

void drawDashedLine(
    ImDrawList* const drawList, ImVec2 const& a, ImVec2 const& b,
    f32 const dashLength, f32 const gapLength, f32 const thickness
) {
    ImVec2 dir{ImVec2(b.x - a.x, b.y - a.y)};
    f32 const length{sqrtf(dir.x * dir.x + dir.y * dir.y)};

    if (length <= 0.0f) {
        return;
    }

    dir.x /= length;
    dir.y /= length;

    f32 pos{0.0f};
    bool draw{true};

    while (pos < length) {
        f32 const seg{draw ? dashLength : gapLength};
        f32 end{pos + seg};

        end = std::min(end, length);

        if (draw) {
            ImVec2 const p1{ImVec2(a.x + dir.x * pos, a.y + dir.y * pos)};
            ImVec2 const p2{ImVec2(a.x + dir.x * end, a.y + dir.y * end)};
            drawList->AddLine(p1, p2, EdStyle::getColorU32(PxGuiCol_DashedFrameBorder), thickness);
        }

        pos = end;
        draw = !draw;
    }
}

void drawDashedRect(
    ImDrawList* const drawList, ImVec2 const& min, ImVec2 const& max,
    f32 const dashLength, f32 const gapLength, f32 const thickness
) {
    drawDashedLine(drawList, ImVec2(min.x, min.y), ImVec2(max.x, min.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(max.x, min.y), ImVec2(max.x, max.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(max.x, max.y), ImVec2(min.x, max.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(min.x, max.y), ImVec2(min.x, min.y), dashLength, gapLength, thickness);
}

void drawDashedWindowBorder(
    ImVec2 const& padding, f32 const dashLength, f32 const gapLength, f32 const thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y + ImGui::GetWindowSize().y)};

    p0.x += padding.x;
    p0.y += padding.y;
    p1.x -= padding.x;
    p1.y -= padding.y;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};

    drawDashedRect(
        dl, p0, p1, dashLength, gapLength, thickness
    );
}

void drawDashedHeader(
    cstring const text, ImVec2 const& padding, f32 textPaddingLeft,
    f32 const dashLength, f32 const gapLength, f32 const thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y)};

    p0.x += padding.x;
    p1.x -= padding.x;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};
    ImVec2 const textSize{ImGui::CalcTextSize(text)};

    f32 constexpr spacing{8.0f};
    f32 const y{p0.y + padding.y};

    f32 const textX{ImMax(p0.x + textPaddingLeft, p0.x)};
    f32 const textEnd{textX + textSize.x};

    f32 const leftLineEnd{ImClamp(textX - spacing, p0.x, p1.x)};
    f32 const rightLineStart{ImClamp(textEnd + spacing, p0.x, p1.x)};

    drawDashedLine(dl, ImVec2(p0.x, y), ImVec2(leftLineEnd, y), dashLength, gapLength, thickness);

    dl->AddText(
        ImVec2(textX, y - textSize.y * 0.5f), EdStyle::getColorU32(ed::PxGuiCol_Text), text
    );

    drawDashedLine(
        dl, ImVec2(rightLineStart, y), ImVec2(p1.x, y), dashLength, gapLength, thickness
    );
}

void drawDashedLineWithGaps(
    ImDrawList* const drawList, ImVec2 const& a, ImVec2 const& b, std::vector<ImVec2> const& gaps,
    f32 const dashLength, f32 const gapLength, f32 const thickness
) {
    f32 const dx{b.x - a.x};
    f32 const dy{b.y - a.y};
    f32 const len{std::sqrt(dx * dx + dy * dy)};

    if (len <= 0.001f) {
        return;
    }
    f32 const dirx{dx / len};
    f32 const diry{dy / len};
    f32 const step{dashLength + gapLength};

    // NOLINTNEXTLINE(*)
    for (f32 t{0}; t < len; t += step) {
        f32 const start{t};
        f32 const end{std::min(t + dashLength, len)};

        f32 const sx{a.x + dirx * start};
        f32 const sy{a.y + diry * start};
        f32 const ex{a.x + dirx * end};

        f32 drawStart{sx};
        f32 const drawEnd{ex};

        for (auto const& g : gaps) {
            if (drawEnd <= g.x || drawStart >= g.y) {
                continue;
            }
            if (drawStart < g.x) {
                drawList->AddLine(
                    ImVec2(drawStart, sy),
                    ImVec2(g.x, sy),
                    EdStyle::getColorU32(PxGuiCol_DashedFrameBorder),
                    thickness
                );
            }
            drawStart = g.y;
        }

        if (drawStart < drawEnd) {
            drawList->AddLine(
                ImVec2(drawStart, sy),
                ImVec2(drawEnd, sy),
                EdStyle::getColorU32(PxGuiCol_DashedFrameBorder),
                thickness
            );
        }
    }
}

} // namespace px::ed
