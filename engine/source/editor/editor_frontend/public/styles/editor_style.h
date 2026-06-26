// © 2026 Pawel Mlynarz

#pragma once

#include "core_minimal.h"
#include "editor_frontend_module.h"

// imgui
#include "imgui.h"

#include <span>
#include <array>

namespace px::ed {

/**
 * Possible to add custom pixi color styles here,
 * provided that the first entry starts with ImGuiCol_COUNT value.
 */
// NOLINTNEXTLINE(cppcoreguidelines-use-enum-class)
enum PxGuiCol : uint8 {
    PxGuiCol_Text = ImGuiCol_COUNT,
    PxGuiCol_TextHovered,
    PxGuiCol_TextActive,
    PxGuiCol_DashedFrameBorder,
    PxGuiCol_FrameBorder,

    PxGuiCol_Count
};

struct StyleConfig {
    StyleConfig();

    ImVec4& operator[](int32 idx);
    ImVec4 const& operator[](int32 idx) const;

  private:
    std::span<ImVec4, ImGuiCol_COUNT> nativeColors_;
    std::array<ImVec4, static_cast<int>(PxGuiCol_Count) - static_cast<int>(ImGuiCol_COUNT)> pxColors_;
};

struct EdStyle {
    static PXEDITOR_FRONTEND_API StyleConfig& getStyle();

    static PXEDITOR_FRONTEND_API ImU32 getColorU32(ImGuiCol idx, float alphaMul = 1.0f);

    static PXEDITOR_FRONTEND_API void setDefaultStyle();
};

} // namespace px::ed
