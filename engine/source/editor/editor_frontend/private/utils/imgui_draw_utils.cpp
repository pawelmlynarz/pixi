// © 2026 Pawel Mlynarz

#include "utils/imgui_draw_utils.h"
#include "styles/editor_style.h"

// imgui
#include "imgui.h"
#include "imgui_internal.h"

namespace px::ed {

void drawDashedLine(
    ImDrawList* const drawList, ImVec2 const& a, ImVec2 const& b,
    float const dashLength, float const gapLength, float const thickness
) {
    ImVec2 dir{ImVec2(b.x - a.x, b.y - a.y)};
    float const length{sqrtf(dir.x * dir.x + dir.y * dir.y)};

    if (length <= 0.0f) {
        return;
    }

    dir.x /= length;
    dir.y /= length;

    float pos{0.0f};
    bool draw{true};

    while (pos < length) {
        float const seg{draw ? dashLength : gapLength};
        float end{pos + seg};

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
    float const dashLength, float const gapLength, float const thickness
) {
    drawDashedLine(drawList, ImVec2(min.x, min.y), ImVec2(max.x, min.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(max.x, min.y), ImVec2(max.x, max.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(max.x, max.y), ImVec2(min.x, max.y), dashLength, gapLength, thickness);
    drawDashedLine(drawList, ImVec2(min.x, max.y), ImVec2(min.x, min.y), dashLength, gapLength, thickness);
}

void drawDashedWindowBorder(
    ImVec2 const& padding, float const dashLength, float const gapLength, float const thickness
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
    char const* const text, ImVec2 const& padding, float textPaddingLeft,
    float const dashLength, float const gapLength, float const thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y)};

    p0.x += padding.x;
    p1.x -= padding.x;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};
    ImVec2 const textSize{ImGui::CalcTextSize(text)};

    float constexpr spacing{8.0f};
    float const y{p0.y + padding.y};

    float const textX{ImMax(p0.x + textPaddingLeft, p0.x)};
    float const textEnd{textX + textSize.x};

    float const leftLineEnd{ImClamp(textX - spacing, p0.x, p1.x)};
    float const rightLineStart{ImClamp(textEnd + spacing, p0.x, p1.x)};

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
    float const dashLength, float const gapLength, float const thickness
) {
    float const dx{b.x - a.x};
    float const dy{b.y - a.y};
    float const len{std::sqrt(dx * dx + dy * dy)};

    if (len <= 0.001f) {
        return;
    }
    float const dirx{dx / len};
    float const diry{dy / len};
    float const step{dashLength + gapLength};

    // NOLINTNEXTLINE(*)
    for (float t{0}; t < len; t += step) {
        float const start{t};
        float const end{std::min(t + dashLength, len)};

        float const sx{a.x + dirx * start};
        float const sy{a.y + diry * start};
        float const ex{a.x + dirx * end};

        float drawStart{sx};
        float const drawEnd{ex};

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
