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

class ImConsole : public ImEditorPanel {
  public:
    ImConsole();

    void Draw() override;

    void OnLogPushed(LogMsg const& LogMsg, std::string const& FormattedMessage);

    ConsoleTextBuffer& GetTextBuf();

  private:
    ConsoleTextBuffer TextBuf_;
    ImGuiTextFilter TextFilter_;
};

inline ConsoleTextBuffer& ImConsole::GetTextBuf() {
    return TextBuf_;
}

} // namespace px::ed
