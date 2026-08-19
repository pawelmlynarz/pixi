// © 2026 Pawel Mlynarz

#pragma once

// containers and strings
#include <array>
#include <span>
#include <string>
#include <string_view>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

// algorithms, ranges and iteration
#include <algorithm>
#include <bit>
#include <iterator>
#include <ranges>

// core vocabulary
#include <concepts>
#include <functional>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

// text formatting and diagnostics
#include <format>
#include <print>
#include <source_location>
#include <stacktrace>

// time, threading and synchronisation
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <mutex>
#include <thread>

// filesystem and streams
#include <filesystem>
#include <fstream>
#include <sstream>

#if PLATFORM_WINDOWS
#include "Windows.h"
#endif

#include "core_minimal.h"
