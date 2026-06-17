// © 2026 Pawel Mlynarz

#include "widgets/panels/header.h"
#include "common/font.h"
#include "utils/imgui_draw_utils.h"

// pxcore
#include "version.h"

namespace px::ed {

namespace {

void DrawVersionInfo() {
    std::string_view constexpr RawVersion{VersionString()};
    std::string const Version{std::format("Pixi Engine Editor v{}", RawVersion.data())};

    PushFont(EImFontSize::Large);

    ImVec2 const WindowSize{ImGui::GetWindowSize()};
    ImVec2 const TextSize{ImGui::CalcTextSize(Version.c_str())};

    ImVec2 const StartPos{
        (WindowSize.x - TextSize.x) * 0.5f,
        (WindowSize.y - TextSize.y) * 0.5f + 5.f
    };

    ImDrawList* const DrawList{ImGui::GetWindowDrawList()};
    ImFont* const Font{ImGui::GetFont()};
    float const FontSize{ImGui::GetFontSize()};

    constexpr std::array Colors{
        IM_COL32(255, 80, 80, 255),  // P
        IM_COL32(80, 255, 80, 255),  // i
        IM_COL32(80, 160, 255, 255), // x
        IM_COL32(255, 200, 80, 255)  // i
    };

    float X{StartPos.x};
    float const Y{StartPos.y};

    std::array<char,2> Buf{0, 0};
    for (int i{0}; i < 4; i++) {
        constexpr std::string_view Prefix{"Pixi"};
        Buf[0] = Prefix[i];
        DrawList->AddText(Font, FontSize, ImVec2(X, Y), Colors[i], Buf.data());
        X += ImGui::CalcTextSize(Buf.data()).x;
    }

    std::string_view const Rest{Version.data() + 4, Version.size() - 4};
    DrawList->AddText(Font, FontSize, ImVec2(X, Y), IM_COL32_WHITE, Rest.data());

    PopFont();
} 

} // namespace

void ImHeader::DrawPanelContent() {
    DrawDashedWindowBorder();

    DrawVersionInfo();
};

} // namespace px::ed
