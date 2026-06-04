// © 2026 Pawel Mlynarz

#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <memory>
#include <optional>
#include <thread>
#include <span>
#include <unordered_map>
#include <type_traits>
#include <filesystem>
#include <fstream>

#if PLATFORM_WINDOWS
#include "Windows.h"
#endif

#include "common/types.h"
#include "tools/asserts.h"
#include "tools/compiler.h"
#include "tools/utility.h"
