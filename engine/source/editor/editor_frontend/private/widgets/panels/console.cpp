// © 2026 Pawel Mlynarz

#include "widgets/panels/console.h"
#include "widgets/foundation/panel_header.h"
#include "widgets/foundation/common_widgets.h"
#include "utils/imgui_draw_utils.h"
#include "utils/imgui_misc.h"

// pxcore
#include "log/log_sink.h"
#include "widgets/foundation/label.h"

namespace px::ed {

namespace {

void RegisterLoggerSink(ImConsole* const Console) {
    SharedPtr OutputLogSink{MakeShared<OutputLogSinkMT>()};

    CustomLoggerSinkCallback CustomSinkCallback;
    CustomSinkCallback.BindRaw(Console, &ImConsole::OnLogPushed);
    OutputLogSink->SetCustomCallback(std::move(CustomSinkCallback));

    DEFINE_OUTPUT_LOG_SINK(std::move(OutputLogSink));
}

void DrawHeader(ImConsole& Console) {
    ImPanelHeader PanelHeader{{.NextWidgetPadding = 50.f}};
    PanelHeader.Begin();

    PanelHeader.AddWidget(
        EWidgetAlignment::Left,
        ImLabel({.Text = "[CONSOLE / LOG]", .FontSize = EImFontSize::Large})
    );

    PanelHeader.AddWidget(
        EWidgetAlignment::Right,
        ImButton({.Text = "Clear", .FontSize = EImFontSize::Large, .bUnderline = true, .OnPressed = [&Console] { Console.GetTextBuf().Clear(); }})
    );

    PanelHeader.AddWidget(
        EWidgetAlignment::Right,
        ImTextFilter({.TextFilterRef = Console.GetTextFilter(), .FontSize = EImFontSize::Medium, .Width = 300})
    );

    PanelHeader.End();
}

void DrawConsoleScrollView(ImConsole& Console) {
    bool AutoScroll{true};

    BeginChildPadded("Scrolling", ImVec2(0, 0), ImVec2(10, 40), 0, ImGuiWindowFlags_HorizontalScrollbar);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiTextFilter const& TextFilter{Console.GetTextFilter()};

        PushFont(EImFontSize::Medium);
        for (auto const& [LogMsg, Color] : Console.GetTextBuf().Lines) {
            ImGui::PushStyleColor(ImGuiCol_Text, Color);
            if (TextFilter.IsActive()) {
                if (TextFilter.PassFilter(LogMsg.c_str(), LogMsg.c_str() + LogMsg.length())) {
                    ImGui::Text(LogMsg.c_str());
                }
            } else {
                ImGui::Text(LogMsg.c_str());
            }
            ImGui::PopStyleColor();
        }
        PopFont();

        ImGui::PopStyleVar();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::EndChild();
}

void DrawConsoleInputField() {
    ImGui::Dummy({0.f, 3.f});
    ImGui::Dummy({10.f, 0.f});
    ImGui::SameLine();

    float const CachedCursorY{ImGui::GetCursorPosY()};
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3.f);
    PushFont(EImFontSize::Medium);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.0f, 1.0f));
    ImGui::Text(">");
    ImGui::PopStyleColor();
    PopFont();
    ImGui::SetCursorPosY(CachedCursorY);
    ImGui::SameLine();

    ImInputField InputField{{.Width = ImGui::GetContentRegionAvail().x - 10.f}};
    InputField.Draw();
}

} // namespace

ImConsole::ImConsole(std::string_view StrId) : ImPanel(StrId) {
    RegisterLoggerSink(this);
}

void ImConsole::DrawPanelContent() {
    DrawDashedWindowBorder();
    DrawHeader(*this);
    DrawConsoleScrollView(*this);
    DrawConsoleInputField();
}

void ImConsole::OnLogPushed(LogMsg const& LogMsg, std::string const& FormattedMessage) {
    static std::unordered_map<ELogVerbosity, ImVec4> Colors{
        {{ELogVerbosity::Trace, ImVec4(.65f, .65f, .65f, 1.f)},
         {ELogVerbosity::Info, ImVec4(.9f, .9f, 0.9f, 1.f)},
         {ELogVerbosity::Warning, ImVec4(.8f, .8f, 0, 1.f)},
         {ELogVerbosity::Error, ImVec4(.8f, 0, 0, 1.f)}}
    };

    ImVec4 const Color{Colors[FromNative(LogMsg.level)]};
    TextBuf_.Lines.emplace_back(FormattedMessage, Color);
};

} // namespace px::ed
