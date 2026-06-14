// © 2026 Pawel Mlynarz

#pragma once

#include "widgets/panel.h"

// pxcore
#include "log/log.h"

namespace px::ed {

struct ConsoleTextBuffer {
    using TextLine = std::pair<std::string, ImVec4>;

    std::list<TextLine> Lines;
    void Clear() { Lines.clear(); }
};

class ImConsole : public ImPanel {
  public:
    ImConsole(std::string_view StrId);

    void OnLogPushed(LogMsg const& LogMsg, std::string const& FormattedMessage);

    ConsoleTextBuffer& GetTextBuf();
    ImGuiTextFilter& GetTextFilter();

  protected:
    void DrawPanelContent() override;

  private:
    ConsoleTextBuffer TextBuf_;
    ImGuiTextFilter TextFilter_;
};

inline ConsoleTextBuffer& ImConsole::GetTextBuf() {
    return TextBuf_;
}

inline ImGuiTextFilter& ImConsole::GetTextFilter() {
    return TextFilter_;
}

} // namespace px::ed
