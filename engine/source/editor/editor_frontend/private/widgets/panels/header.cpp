// © 2026 Pawel Mlynarz

#include "widgets/panels/header.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

// pxcore
#include "version.h"

namespace px::ed {

namespace {

void drawVersionInfo() {
    std::string_view constexpr rawVersion{VersionString()};
    std::string const version{std::format("Pixi Engine Editor v{}", rawVersion.data())};

    pushFont(EImFontSize::Large);

    ImVec2 const windowSize{ImGui::GetWindowSize()};
    ImVec2 const textSize{ImGui::CalcTextSize(version.c_str())};

    ImVec2 const startPos{
        (windowSize.x - textSize.x) * 0.5f,
        (windowSize.y - textSize.y) * 0.5f + 5.f
    };

    ImDrawList* const drawList{ImGui::GetWindowDrawList()};
    ImFont* const font{ImGui::GetFont()};
    float const fontSize{ImGui::GetFontSize()};

    constexpr std::array colors{
        IM_COL32(255, 80, 80, 255),  // P
        IM_COL32(80, 255, 80, 255),  // i
        IM_COL32(80, 160, 255, 255), // x
        IM_COL32(255, 200, 80, 255)  // i
    };

    float x{startPos.x};
    float const y{startPos.y};

    std::array<char, 2> buf{0, 0};
    for (int i{0}; i < 4; i++) {
        constexpr std::string_view prefix{"Pixi"};
        buf[0] = prefix[i];
        drawList->AddText(font, fontSize, ImVec2(x, y), colors[i], buf.data());
        x += ImGui::CalcTextSize(buf.data()).x;
    }

    std::string_view const rest{version.data() + 4, version.size() - 4};
    drawList->AddText(font, fontSize, ImVec2(x, y), IM_COL32_WHITE, rest.data());

    popFont();
}

} // namespace

void ImHeader::drawPanelContent() {
    drawDashedWindowBorder();

    drawVersionInfo();
};

} // namespace px::ed
