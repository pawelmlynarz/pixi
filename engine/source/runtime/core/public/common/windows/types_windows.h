// © 2026 Pawel Mlynarz

#pragma once

#include <cstddef>
#include <cstdint>

// clang-format off

using u8		= std::uint8_t;
using u16		= std::uint16_t;
using u32		= std::uint32_t;
using u64		= std::uint64_t;

using i8		= std::int8_t;
using i16		= std::int16_t;
using i32		= std::int32_t;
using i64		= std::int64_t;

using f32		= float;
using f64		= double;

using cstring	= const char*;

constexpr u64 kU64Max	= UINT64_MAX;
constexpr i64 kI64Max	= INT64_MAX;
constexpr u32 kU32Max	= UINT32_MAX;
constexpr i32 kI32Max	= INT32_MAX;
constexpr u16 kU16Max	= UINT16_MAX;
constexpr i16 kI16Max	= INT16_MAX;
constexpr u8  kU8Max	= UINT8_MAX;
constexpr i8  kI8Max	= INT8_MAX;

constexpr size_t kDefaultAlign{4};

// clang-format on
