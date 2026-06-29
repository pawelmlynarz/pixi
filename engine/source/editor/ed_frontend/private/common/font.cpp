// © 2026 Pawel Mlynarz

#include "common/font.h"

// imgui
#include "imgui.h"

namespace px::ed {

namespace {

ImFont* addDefaultFont(float const size) {
    ImGuiIO& io{ImGui::GetIO()};

    ImFontConfig config;
    config.SizePixels = size;
    config.OversampleH = config.OversampleV = 1;
    config.PixelSnapH = true;

    return io.Fonts->AddFontDefault(&config);
}

struct StaticFontHub {
    static void ensureInitialized() {
        if (fontStorage[0] != nullptr) {
            return;
        }
        fontStorage[enumCast(EImFontSize::Small)] = addDefaultFont(14.0f);
        fontStorage[enumCast(EImFontSize::Medium)] = addDefaultFont(18.0f);
        fontStorage[enumCast(EImFontSize::Large)] = addDefaultFont(22.0f);
    }
    static inline std::array<ImFont*, enumCast<EImFontSize>(EImFontSize::Max)> fontStorage;
};

} // namespace

void pushFont(EImFontSize const fontSize) {
    StaticFontHub::ensureInitialized();
    ImGui::PushFont(StaticFontHub::fontStorage[enumCast(fontSize)]);
}

void popFont() {
    ImGui::PopFont();
}

} // namespace px::ed
