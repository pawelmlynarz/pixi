// © 2026 Pawel Mlynarz

#pragma once

// clang-format off

#define PX_TODO(msg) void(msg)

#include <cassert>
#define PX_ASSERT(condition) assert((condition))
#define PX_ASSERT_MSG(condition, message) PX_ASSERT((condition) && (message))

// clang-format on
