// © 2026 Pawel Mlynarz

#include "utils/imgui_misc.h"

namespace px::ed {

bool BeginChildPadded(char const* const StrId, ImVec2 const& Size, ImVec2 const& Padding, ImGuiChildFlags const ChildFlags, ImGuiWindowFlags const WindowFlags) {
    ImVec2 const RegionAvail{ImGui::GetContentRegionAvail()};
    ImVec2 const Cursor{ImGui::GetCursorPos()};

    ImGui::SetCursorPos(ImVec2(Cursor.x + Padding.x, Cursor.y + Padding.y));

    ImVec2 const ChildSize(
        (Size.x == 0.f && Size.y == 0.f) ? ImVec2(RegionAvail.x - Padding.x * 2.0f, RegionAvail.y - Padding.y * 2.0f) : Size
    );

    return ImGui::BeginChild(StrId, ChildSize, ChildFlags, WindowFlags);
}

} // namespace px::ed
