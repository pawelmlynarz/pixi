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

void registerLoggerSink(ImConsole* const console) {
    SharedPtr const outputLogSink{makeShared<OutputLogSinkMT>()};

    CustomLoggerSinkCallback customSinkCallback;
    customSinkCallback.bindRaw(console, &ImConsole::onLogPushed);
    outputLogSink->setCustomCallback(std::move(customSinkCallback));

    DEFINE_OUTPUT_LOG_SINK(outputLogSink);
}

void drawHeader(ImConsole& console) {
    ImPanelHeader panelHeader{{.NextWidgetPadding = 50.f}};
    panelHeader.begin();

    panelHeader.addWidget(
        EWidgetAlignment::Left,
        ImLabel({.Text = "[CONSOLE / LOG]", .FontSize = EImFontSize::Large})
    );

    panelHeader.addWidget(
        EWidgetAlignment::Right,
        ImButton({.Text = "Clear", .FontSize = EImFontSize::Large, .bUnderline = true, .OnPressed = [&console] { console.getTextBuf().clear(); }})
    );

    panelHeader.addWidget(
        EWidgetAlignment::Right,
        ImTextFilter({.TextFilterRef = console.getTextFilter(), .FontSize = EImFontSize::Medium, .Width = 300})
    );

    panelHeader.end();
}

void drawConsoleScrollView(ImConsole& console) {
    bool constexpr autoScroll{true};

    beginChildPadded("Scrolling", ImVec2(0, 0), ImVec2(10, 40), 0, ImGuiWindowFlags_HorizontalScrollbar);
    {
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        ImGuiTextFilter const& textFilter{console.getTextFilter()};

        pushFont(EImFontSize::Medium);
        for (auto const& [LogMsg, Color] : console.getTextBuf().Lines) {
            ImGui::PushStyleColor(ImGuiCol_Text, Color);
            if (textFilter.IsActive()) {
                if (textFilter.PassFilter(LogMsg.c_str(), LogMsg.c_str() + LogMsg.length())) {
                    ImGui::Text(LogMsg.c_str());
                }
            } else {
                ImGui::Text(LogMsg.c_str());
            }
            ImGui::PopStyleColor();
        }
        popFont();

        ImGui::PopStyleVar();

        if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
            ImGui::SetScrollHereY(1.0f);
        }
    }
    ImGui::EndChild();
}

void drawConsoleInputField() {
    ImGui::Dummy({0.f, 3.f});
    ImGui::Dummy({10.f, 0.f});
    ImGui::SameLine();

    float const cachedCursorY{ImGui::GetCursorPosY()};
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 3.f);
    pushFont(EImFontSize::Medium);
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.8f, 0.8f, 0.0f, 1.0f));
    ImGui::Text(">");
    ImGui::PopStyleColor();
    popFont();
    ImGui::SetCursorPosY(cachedCursorY);
    ImGui::SameLine();

    ImInputField const inputField{{.Width = ImGui::GetContentRegionAvail().x - 10.f}};
    inputField.draw();
}

} // namespace

ImConsole::ImConsole(std::string_view strId) : ImPanel(strId) {
    registerLoggerSink(this);
}

void ImConsole::drawPanelContent() {
    drawDashedWindowBorder();
    drawHeader(*this);
    drawConsoleScrollView(*this);
    drawConsoleInputField();
}

void ImConsole::onLogPushed(LogMsg const& logMsg, std::string const& formattedMessage) {
    static std::unordered_map<ELogVerbosity, ImVec4> colors{
        {{ELogVerbosity::Trace, ImVec4(.65f, .65f, .65f, 1.f)},
         {ELogVerbosity::Info, ImVec4(.9f, .9f, 0.9f, 1.f)},
         {ELogVerbosity::Warning, ImVec4(.8f, .8f, 0, 1.f)},
         {ELogVerbosity::Error, ImVec4(.8f, 0, 0, 1.f)}}
    };

    ImVec4 const color{colors[fromNative(logMsg.level)]};
    textBuf_.Lines.emplace_back(formattedMessage, color);
};

} // namespace px::ed
