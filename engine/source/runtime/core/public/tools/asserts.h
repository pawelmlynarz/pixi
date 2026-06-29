// © 2026 Pawel Mlynarz

#pragma once

// NOLINTBEGIN
// clang-format off

#include "common/types.h"
#include "tools/compiler.h"

#include <string>
#include <format>
#include <source_location>

#define pxToDo(Msg) void(Msg)

#if defined(_MSC_VER)
#define DEBUG_BREAK() (__nop(), __debugbreak())
#elif defined(__clang__) || defined(__GNUC__)
#define DEBUG_BREAK() __builtin_trap()
#endif

#define BREAK_AND_RETURN_FALSE() (DEBUG_BREAK(), false)
#define BREAK_AND_ABORT() \
    do {                  \
        DEBUG_BREAK();    \
        std::abort();     \
    } while (0)

namespace px::asserts {

using namespace px;

template <uint64 UID>
std::atomic_bool ensureHasExecuted{false};

constexpr uint64 fileLineHashForEnsure(std::source_location const& loc = std::source_location::current()) {
    uint32 result{2166136261u};
    char const* filename{loc.file_name()};
    for (; *filename; ++filename) {
        result ^= static_cast<uint8>(*filename);
        result *= 16777619u;
    }
    return (static_cast<uint64>(result) << 32) | loc.line();
}

inline std::string getTranslationUnitInfo(std::source_location const& Loc = std::source_location::current()) {
    return std::format("In function {} on line {}", Loc.function_name(), Loc.line());
}

PXENGINE_API bool execEnsureCheck(bool const bAlways, std::atomic_bool& bExecuted, std::string const& translationUnitInfo, std::string const& message = {});

PXENGINE_API bool execAssertCheck(std::string const& translationUnitInfo, std::string const& message = {});

} // namespace px::asserts

#if !defined(DO_ENSURE)
#define DO_ENSURE defined(_DEBUG)
#endif

#if !defined(DO_CHECK)
#define DO_CHECK defined(_DEBUG)
#endif

#define PX_ENSURE_IMPL(always, expr, ...)                                           \
    (                                                                               \
        !!(expr) ||                                                                 \
        (px::asserts::execEnsureCheck(                                              \
             always,                                                                \
             px::asserts::ensureHasExecuted<px::asserts::fileLineHashForEnsure()>,  \
             px::asserts::getTranslationUnitInfo(),                                 \
             ##__VA_ARGS__                                                          \
         ) &&                                                                       \
         BREAK_AND_RETURN_FALSE()))

#define pxEnsure(expr) \
    PX_ENSURE_IMPL(false, expr)

#define pxEnsureAlways(expr) \
    PX_ENSURE_IMPL(true, expr)

#define pxEnsureMsgf(expr, fmt, ...) \
    PX_ENSURE_IMPL(false, expr, std::format(fmt, __VA_ARGS__))

#define pxEnsureAlwaysMsgf(expr, fmt, ...) \
    PX_ENSURE_IMPL(true, expr, fmt, __VA_ARGS__)

#define pxEnsureReturnIfFalse(condition, ...) \
    if (!(condition)) {                     \
        Ensure(false);                      \
        return __VA_OPT__(__VA_ARGS__);     \
    }

#define pxReturnIfFalse(condition, ...)   \
    if (!(condition)) {                 \
        return __VA_OPT__(__VA_ARGS__); \
    }

#define pxEnsureContinueIfFalse(condition) \
    if (!(condition)) {                  \
        Ensure(false);                   \
        continue;                        \
    }

#define pxContinueIfFalse(condition) \
    if (!(condition)) {            \
        continue;                  \
    }

#define pxEnsureNoEntry(fmt, ...) \
    pxEnsureAlwaysMsgf(false, fmt, __VA_ARGS__)

#define PX_ASSERT_IMPL(expr, ...)                       \
    if (!(expr)) {                                      \
        if (px::asserts::execAssertCheck(               \
                px::asserts::getTranslationUnitInfo(),  \
                ##__VA_ARGS__                           \
            ))                                          \
            BREAK_AND_ABORT();                          \
    }                                                   \
    (void)0

#define pxAssert(expr) PX_ASSERT_IMPL(expr)

#define pxAssertMsgf(expr, fmt, ...) PX_ASSERT_IMPL(expr, std::format(fmt, __VA_ARGS__))

#define pxNotImplemented() \
    pxEnsureNoEntry("Not implemented function")

// NOLINTEND
// clang-format on
