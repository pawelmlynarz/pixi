// © 2026 Pawel Mlynarz

#include "common/font.h"

// pxcore
#include "tools/utility.h"

// imgui
#include "imgui.h"

namespace px::ed {

namespace {

ImFont* AddDefaultFont(float const Size) {
    ImGuiIO& IO{ImGui::GetIO()};

    ImFontConfig Config;
    Config.SizePixels = Size;
    Config.OversampleH = Config.OversampleV = 1;
    Config.PixelSnapH = true;

    return IO.Fonts->AddFontDefault(&Config);
}

struct StaticFontHub {
    static void EnsureInitialized() {
        if (FontStorage[0] != nullptr) {
            return;
        }
        FontStorage[EnumCast(EImFontSize::Small)] = AddDefaultFont(14.0f);
        FontStorage[EnumCast(EImFontSize::Medium)] = AddDefaultFont(18.0f);
        FontStorage[EnumCast(EImFontSize::Large)] = AddDefaultFont(22.0f);
    }
    static inline std::array<ImFont*, EnumCast<EImFontSize>(EImFontSize::Max)> FontStorage;
};

} // namespace

void PushFont(EImFontSize const FontSize) {
    StaticFontHub::EnsureInitialized();
    ImGui::PushFont(StaticFontHub::FontStorage[EnumCast(FontSize)]);
}

void PopFont() {
    ImGui::PopFont();
}

} // namespace px::ed
