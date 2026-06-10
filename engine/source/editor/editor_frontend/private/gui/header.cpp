// © 2026 Pawel Mlynarz

#include "gui/header.h"
#include "gui/gui_const.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

// pxcore
#include "version.h"

namespace px::ed {

namespace {

void DrawVersionInfo() {
    std::string_view constexpr RawVersion{VersionString()};
    std::string const Version{std::format("Pixi Engine Editor v{}", RawVersion.data())};

    edimgui::PushFont(edimgui::EImGuiFontSize::Large);

    ImVec2 const WindowSize{ImGui::GetWindowSize()};
    ImVec2 const TextSize{ImGui::CalcTextSize(Version.c_str())};

    ImVec2 const StartPos{
        (WindowSize.x - TextSize.x) * 0.5f,
        (WindowSize.y - TextSize.y) * 0.5f
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
    float Y{StartPos.y};
    
    char Buf[2]{0, 0};
    for (int i{0}; i < 4; i++) {
        constexpr std::string_view Prefix {"Pixi"};
        *Buf = Prefix[i];
        DrawList->AddText(Font, FontSize, ImVec2(X, Y), Colors[i], Buf);
        X += ImGui::CalcTextSize(Buf).x;
    }

    std::string_view const Rest{Version.data() + 4, Version.size() - 4};
    DrawList->AddText(Font, FontSize, ImVec2(X, Y), IM_COL32_WHITE, Rest.data());

    edimgui::PopFont();
}

} // namespace

void ImHeader::Draw() {
    ImGui::Begin(NameHeader, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();

        DrawVersionInfo();
    }
    ImGui::End();
};

} // namespace px::ed
