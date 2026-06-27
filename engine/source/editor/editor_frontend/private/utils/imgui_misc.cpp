// © 2026 Pawel Mlynarz

#include "utils/imgui_misc.h"

namespace px::ed {

bool beginChildPadded(char const* const strId, ImVec2 const& size, ImVec2 const& padding, ImGuiChildFlags const childFlags, ImGuiWindowFlags const windowFlags) {
    ImVec2 const regionAvail{ImGui::GetContentRegionAvail()};
    ImVec2 const cursor{ImGui::GetCursorPos()};

    ImGui::SetCursorPos(ImVec2(cursor.x + padding.x, cursor.y + padding.y));

    ImVec2 const childSize(
        (size.x == 0.f && size.y == 0.f) ? ImVec2(regionAvail.x - padding.x * 2.0f, regionAvail.y - padding.y * 2.0f) : size
    );

    return ImGui::BeginChild(strId, childSize, childFlags, windowFlags);
}

} // namespace px::ed
