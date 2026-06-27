// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

// pxcore
#include "log/log.h"

namespace px::ed {

struct ConsoleTextBuffer {
    using TextLine = std::pair<std::string, ImVec4>;

    std::list<TextLine> Lines;
    void clear() { Lines.clear(); }
};

class ImConsole : public ImPanel {
  public:
    ImConsole(std::string_view strId);

    void onLogPushed(LogMsg const& logMsg, std::string const& formattedMessage);

    ConsoleTextBuffer& getTextBuf();
    ImGuiTextFilter& getTextFilter();

  protected:
    void drawPanelContent() override;

  private:
    ConsoleTextBuffer textBuf_;
    ImGuiTextFilter textFilter_;
};

inline ConsoleTextBuffer& ImConsole::getTextBuf() {
    return textBuf_;
}

inline ImGuiTextFilter& ImConsole::getTextFilter() {
    return textFilter_;
}

} // namespace px::ed
