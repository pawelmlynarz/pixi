// © 2026 Pawel Mlynarz

#include "imgui/imgui_draw_utils.h"

// pxcore
#include "tools/utility.h"

// imgui
#include "imgui.h"
#include "imgui_internal.h"

namespace px::edimgui {

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
        if (FontStorage[0] != nullptr)
            return;
        FontStorage[EnumCast(EImGuiFontSize::Small)] = AddDefaultFont(14.0f);
        FontStorage[EnumCast(EImGuiFontSize::Medium)] = AddDefaultFont(18.0f);
        FontStorage[EnumCast(EImGuiFontSize::Large)] = AddDefaultFont(22.0f);
    }
    static inline std::array<ImFont*, EnumCast<EImGuiFontSize>(EImGuiFontSize::Max)> FontStorage;
};

} // namespace

void DrawDashedLine(
    ImDrawList* const DrawList, ImVec2 const& A, ImVec2 const& B, ImU32 const Color,
    float const DashLength, float const GapLength, float const Thickness
) {
    ImVec2 Dir{ImVec2(B.x - A.x, B.y - A.y)};
    float const Length{sqrtf(Dir.x * Dir.x + Dir.y * Dir.y)};

    if (Length <= 0.0f) {
        return;
    }

    Dir.x /= Length;
    Dir.y /= Length;

    float Pos{0.0f};
    bool Draw{true};

    while (Pos < Length) {
        float const Seg{Draw ? DashLength : GapLength};
        float End{Pos + Seg};

        End = std::min(End, Length);

        if (Draw) {
            ImVec2 const p1{ImVec2(A.x + Dir.x * Pos, A.y + Dir.y * Pos)};
            ImVec2 const p2{ImVec2(A.x + Dir.x * End, A.y + Dir.y * End)};
            DrawList->AddLine(p1, p2, Color, Thickness);
        }

        Pos = End;
        Draw = !Draw;
    }
}

void DrawDashedRect(
    ImDrawList* const DrawList, ImVec2 const& Min, ImVec2 const& Max, ImU32 const Color,
    float const DashLength, float const GapLength, float const Thickness
) {
    DrawDashedLine(DrawList, ImVec2(Min.x, Min.y), ImVec2(Max.x, Min.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Max.x, Min.y), ImVec2(Max.x, Max.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Max.x, Max.y), ImVec2(Min.x, Max.y), Color, DashLength, GapLength, Thickness);
    DrawDashedLine(DrawList, ImVec2(Min.x, Max.y), ImVec2(Min.x, Min.y), Color, DashLength, GapLength, Thickness);
}

void DrawDashedWindowBorder(
    ImVec2 const& Padding, ImColor const Color, float const DashLength, float const GapLength, float const Thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y + ImGui::GetWindowSize().y)};

    p0.x += Padding.x;
    p0.y += Padding.y;
    p1.x -= Padding.x;
    p1.y -= Padding.y;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};

    DrawDashedRect(
        dl, p0, p1, Color, DashLength, GapLength, Thickness
    );
}

void DrawDashedHeader(
    char const* const Text, ImVec2 const& Padding, float TextPaddingLeft, ImColor const LineColor, ImColor const TextColor,
    float const DashLength, float const GapLength, float const Thickness
) {
    ImVec2 p0{ImGui::GetWindowPos()};
    ImVec2 p1{ImVec2(p0.x + ImGui::GetWindowSize().x, p0.y)};

    p0.x += Padding.x;
    p1.x -= Padding.x;

    ImDrawList* const dl{ImGui::GetWindowDrawList()};
    ImVec2 const TextSize{ImGui::CalcTextSize(Text)};

    float constexpr Spacing{8.0f};
    float const y{p0.y + Padding.y};

    float const TextX{ImMax(p0.x + TextPaddingLeft, p0.x)};
    float const TextEnd{TextX + TextSize.x};

    float const LeftLineEnd{ImClamp(TextX - Spacing, p0.x, p1.x)};
    float const RightLineStart{ImClamp(TextEnd + Spacing, p0.x, p1.x)};

    DrawDashedLine(dl, ImVec2(p0.x, y), ImVec2(LeftLineEnd, y), LineColor, DashLength, GapLength, Thickness);

    dl->AddText(
        ImVec2(TextX, y - TextSize.y * 0.5f), TextColor, Text
    );

    DrawDashedLine(
        dl, ImVec2(RightLineStart, y), ImVec2(p1.x, y), LineColor, DashLength, GapLength, Thickness
    );
}

void DrawDashedLineWithGaps(
    ImDrawList* const DrawList, ImVec2 const& A, ImVec2 const& B, std::vector<ImVec2> const& Gaps,
    ImColor LineColor, float const DashLength, float const GapLength, float const Thickness
) {
    float const Dx{B.x - A.x};
    float const Dy{B.y - A.y};
    float const Len{std::sqrt(Dx * Dx + Dy * Dy)};

    if (Len <= 0.001f) {
        return;
    }
    float const Dirx{Dx / Len};
    float const Diry{Dy / Len};
    float const Step{DashLength + GapLength};

    for (float t{0}; t < Len; t += Step) {
        float const Start{t};
        float const End{std::min(t + DashLength, Len)};

        float const Sx{A.x + Dirx * Start};
        float const Sy{A.y + Diry * Start};
        float const Ex{A.x + Dirx * End};

        float DrawStart{Sx};
        float const DrawEnd{Ex};

        for (auto const& g : Gaps) {
            if (DrawEnd <= g.x || DrawStart >= g.y) {
                continue;
            }
            if (DrawStart < g.x) {
                DrawList->AddLine(
                    ImVec2(DrawStart, Sy),
                    ImVec2(g.x, Sy),
                    LineColor,
                    Thickness
                );
            }
            DrawStart = g.y;
        }

        if (DrawStart < DrawEnd) {
            DrawList->AddLine(
                ImVec2(DrawStart, Sy),
                ImVec2(DrawEnd, Sy),
                LineColor,
                Thickness
            );
        }
    }
}

void PushFont(EImGuiFontSize const FontSize) {
    StaticFontHub::EnsureInitialized();
    ImGui::PushFont(StaticFontHub::FontStorage[EnumCast(FontSize)]);
}

void PopFont() {
    ImGui::PopFont();
}

bool BeginChildPadded(char const* const StrId, ImVec2 const& Size, ImVec2 const& Padding, ImGuiChildFlags const ChildFlags, ImGuiWindowFlags const WindowFlags) {
    ImVec2 const RegionAvail{ImGui::GetContentRegionAvail()};
    ImVec2 Cursor{ImGui::GetCursorPos()};

    ImGui::SetCursorPos(ImVec2(Cursor.x + Padding.x, Cursor.y + Padding.y));

    ImVec2 const ChildSize(
        (Size.x == 0.f && Size.y == 0.f) ? ImVec2(RegionAvail.x - Padding.x * 2.0f, RegionAvail.y - Padding.y * 2.0f) : Size
    );

    return ImGui::BeginChild(StrId, ChildSize, ChildFlags, WindowFlags);
}

bool Button(char const* const Label, bool const bUnderline, ImColor Color, ImColor HoveredColor, ImColor PressedColor) {
    ImGuiWindow* const Window{ImGui::GetCurrentWindow()};

    if (Window->SkipItems) {
        return false;
    }
    ImGuiID const ID{Window->GetID(Label)};

    ImVec2 const TextSize{ImGui::CalcTextSize(Label)};
    ImVec2 const Pos{ImGui::GetCursorScreenPos()};
    ImRect const BB(Pos, ImVec2(Pos.x + TextSize.x, Pos.y + TextSize.y));

    ImGui::ItemSize(BB);
    if (!ImGui::ItemAdd(BB, ID)) {
        return false;
    }
    bool const bHovered{ImGui::ItemHoverable(BB, ID, 0)};
    bool const bClicked{bHovered && ImGui::IsMouseReleased(0)};
    bool const bPressed{bHovered && ImGui::IsMouseDown(0)};

    ImU32 TextColor{Color};
    if (bPressed) {
        TextColor = PressedColor;
    } else if (bHovered) {
        TextColor = HoveredColor;
    }
    Window->DrawList->AddText(Pos, TextColor, Label);

    if (bUnderline) {
        ImVec2 const UnderlineStart(Pos.x, Pos.y + TextSize.y);
        ImVec2 const UnderlineEnd(Pos.x + TextSize.x, Pos.y + TextSize.y);

        Window->DrawList->AddLine(UnderlineStart, UnderlineEnd, TextColor, 1.f);
    }
    return bClicked;
}

} // namespace px::edimgui
