// © 2026 Pawel Mlynarz

#pragma once

// imgui
#include "imgui.h"

namespace px::ed {

/**
 * Same as ImGui::BeginChild, but adds additional padding for the child window from the parent borders.
 */
bool beginChildPadded(char const* strId, ImVec2 const& size = ImVec2(0, 0), ImVec2 const& padding = ImVec2(0, 0), ImGuiChildFlags childFlags = 0, ImGuiWindowFlags windowFlags = 0);

} // namespace px::ed
