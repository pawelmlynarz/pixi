// © 2026 Pawel Mlynarz

#pragma once

#include "editor_widget.h"

// pxcore
#include "log/log.h"

namespace px::ed {

class ImConsole : public ImGuiEditorWidget {
  public:
    ImConsole();

    void Draw() override;

    void OnLogPushed(LogMsg const& LogMsg, std::string const& FormattedMessage);

  private:
    struct ConsoleTextBuffer {
        using TextLine = std::pair<std::string, ImVec4>;

        std::list<TextLine> Lines;
        void Clear() { Lines.clear(); }
    };

    ConsoleTextBuffer TextBuf_;
    ImGuiTextFilter TextFilter_;
};

} // namespace px::ed
