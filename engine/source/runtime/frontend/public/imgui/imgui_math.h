// © 2026 Pawel Mlynarz

#pragma once

// imgui
#include "imgui.h"

// clang-format off
// NOLINTBEGIN

// Copy paste from imgui.h to avoid the need for defining
// IMGUI_DEFINE_MATH_OPERATORS which is not handy at all ( must be declared before imgui.h ).

// ImVec2 operators
inline ImVec2  operator*(const ImVec2& lhs, const float rhs)    { return ImVec2(lhs.x * rhs, lhs.y * rhs); }
inline ImVec2  operator*(const float lhs, const ImVec2& rhs)    { return ImVec2(lhs * rhs.x, lhs * rhs.y); }
inline ImVec2  operator/(const ImVec2& lhs, const float rhs)    { return ImVec2(lhs.x / rhs, lhs.y / rhs); }
inline ImVec2  operator+(const ImVec2& lhs, const ImVec2& rhs)  { return ImVec2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline ImVec2  operator-(const ImVec2& lhs, const ImVec2& rhs)  { return ImVec2(lhs.x - rhs.x, lhs.y - rhs.y); }
inline ImVec2  operator*(const ImVec2& lhs, const ImVec2& rhs)  { return ImVec2(lhs.x * rhs.x, lhs.y * rhs.y); }
inline ImVec2  operator/(const ImVec2& lhs, const ImVec2& rhs)  { return ImVec2(lhs.x / rhs.x, lhs.y / rhs.y); }
inline ImVec2  operator+(const ImVec2& lhs)                     { return lhs; }
inline ImVec2  operator-(const ImVec2& lhs)                     { return ImVec2(-lhs.x, -lhs.y); }
inline ImVec2& operator*=(ImVec2& lhs, const float rhs)         { lhs.x *= rhs; lhs.y *= rhs; return lhs; }
inline ImVec2& operator/=(ImVec2& lhs, const float rhs)         { lhs.x /= rhs; lhs.y /= rhs; return lhs; }
inline ImVec2& operator+=(ImVec2& lhs, const ImVec2& rhs)       { lhs.x += rhs.x; lhs.y += rhs.y; return lhs; }
inline ImVec2& operator-=(ImVec2& lhs, const ImVec2& rhs)       { lhs.x -= rhs.x; lhs.y -= rhs.y; return lhs; }
inline ImVec2& operator*=(ImVec2& lhs, const ImVec2& rhs)       { lhs.x *= rhs.x; lhs.y *= rhs.y; return lhs; }
inline ImVec2& operator/=(ImVec2& lhs, const ImVec2& rhs)       { lhs.x /= rhs.x; lhs.y /= rhs.y; return lhs; }
inline bool    operator==(const ImVec2& lhs, const ImVec2& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
inline bool    operator!=(const ImVec2& lhs, const ImVec2& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y; }

// ImVec4 operators
inline ImVec4  operator*(const ImVec4& lhs, const float rhs)    { return ImVec4(lhs.x * rhs, lhs.y * rhs, lhs.z * rhs, lhs.w * rhs); }
inline ImVec4  operator*(const float lhs, const ImVec4& rhs)    { return ImVec4(lhs * rhs.x, lhs * rhs.y, lhs * rhs.z, lhs * rhs.w); }
inline ImVec4  operator/(const ImVec4& lhs, const float rhs)    { return ImVec4(lhs.x / rhs, lhs.y / rhs, lhs.z / rhs, lhs.w / rhs); }
inline ImVec4  operator+(const ImVec4& lhs, const ImVec4& rhs)  { return ImVec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w); }
inline ImVec4  operator-(const ImVec4& lhs, const ImVec4& rhs)  { return ImVec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w); }
inline ImVec4  operator*(const ImVec4& lhs, const ImVec4& rhs)  { return ImVec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w); }
inline ImVec4  operator/(const ImVec4& lhs, const ImVec4& rhs)  { return ImVec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w); }
inline ImVec4  operator+(const ImVec4& lhs)                     { return lhs; }
inline ImVec4  operator-(const ImVec4& lhs)                     { return ImVec4(-lhs.x, -lhs.y, -lhs.z, -lhs.w); }
inline ImVec4& operator*=(ImVec4& lhs, const float rhs)         { lhs.x *= rhs; lhs.y *= rhs; lhs.z *= rhs; lhs.w *= rhs; return lhs; }
inline ImVec4& operator/=(ImVec4& lhs, const float rhs)         { lhs.x /= rhs; lhs.y /= rhs; lhs.z /= rhs; lhs.w /= rhs; return lhs; }
inline ImVec4& operator+=(ImVec4& lhs, const ImVec4& rhs)       { lhs.x += rhs.x; lhs.y += rhs.y; lhs.z += rhs.z; lhs.w += rhs.w; return lhs; }
inline ImVec4& operator-=(ImVec4& lhs, const ImVec4& rhs)       { lhs.x -= rhs.x; lhs.y -= rhs.y; lhs.z -= rhs.z; lhs.w -= rhs.w; return lhs; }
inline ImVec4& operator*=(ImVec4& lhs, const ImVec4& rhs)       { lhs.x *= rhs.x; lhs.y *= rhs.y; lhs.z *= rhs.z; lhs.w *= rhs.w; return lhs; }
inline ImVec4& operator/=(ImVec4& lhs, const ImVec4& rhs)       { lhs.x /= rhs.x; lhs.y /= rhs.y; lhs.z /= rhs.z; lhs.w /= rhs.w; return lhs; }
inline bool    operator==(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w; }
inline bool    operator!=(const ImVec4& lhs, const ImVec4& rhs) { return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w; }

// NOLINTEND
// clang-format on
