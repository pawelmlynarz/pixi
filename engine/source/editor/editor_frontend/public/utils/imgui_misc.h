// © 2026 Pawel Mlynarz

#pragma once

// imgui
#include "imgui.h"

namespace px::ed {

/**
 * Same as ImGui::BeginChild, but adds additional padding for the child window from the parent borders.
 */
bool BeginChildPadded(char const* StrId, ImVec2 const& Size = ImVec2(0, 0), ImVec2 const& Padding = ImVec2(0, 0), ImGuiChildFlags ChildFlags = 0, ImGuiWindowFlags WindowFlags = 0);

} // namespace px::ed
