// © 2026 Pawel Mlynarz

#include "panels/console.h"
#include "common/common_widgets.h"

#include "imgui/imgui_draw_utils.h"
#include "imgui/imgui_editor_helper.h"

// pxcore
#include "log/log_sink.h"

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
    ImPanelHeader PanelHeader;
    PanelHeader.Begin({.NextWidgetPadding = 50.f});

    PanelHeader.AddWidget(
        EWidgetAlignment::Left,
        ImLabel({.Text = "[CONSOLE / LOG]", .FontSize = edimgui::EImGuiFontSize::Large})
    );

    PanelHeader.AddWidget(
        EWidgetAlignment::Right,
        ImButton({.Text = "Clear", .FontSize = edimgui::EImGuiFontSize::Large, .bUnderline = true, .OnPressed = [&Console] { Console.GetTextBuf().Clear(); }})
    );

    PanelHeader.AddWidget(
        EWidgetAlignment::Right,
        ImTextFilter({.TextFilterRef = Console.GetTextFilter(), .FontSize = edimgui::EImGuiFontSize::Medium, .Width = 300})
    );

    PanelHeader.End();
}

} // namespace

ImConsole::ImConsole() {
    RegisterLoggerSink(this);
}

void ImConsole::Draw() {
    ImGui::Begin(NameConsole, nullptr, edimgui::GetEditorWidgetFlags());
    {
        edimgui::DrawDashedWindowBorder();

        DrawHeader(*this);

        bool AutoScroll{true};

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(100, 100));

        edimgui::BeginChildPadded("Scrolling", ImVec2(0, 0), ImVec2(10, 30), 0, ImGuiWindowFlags_HorizontalScrollbar);
        {
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

            edimgui::PushFont(edimgui::EImGuiFontSize::Medium);
            for (auto const& [logMsg, color] : TextBuf_.Lines) {
                ImGui::PushStyleColor(ImGuiCol_Text, color);
                if (TextFilter_.IsActive()) {
                    if (TextFilter_.PassFilter(logMsg.c_str(), logMsg.c_str() + logMsg.length())) {
                        ImGui::Text(logMsg.c_str());
                    }
                } else {
                    ImGui::Text(logMsg.c_str());
                }
                ImGui::PopStyleColor();
            }
            edimgui::PopFont();

            ImGui::PopStyleVar();

            if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                ImGui::SetScrollHereY(1.0f);
            }
        }
        ImGui::EndChild();

        ImGui::PopStyleVar();
    }
    ImGui::End();
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
