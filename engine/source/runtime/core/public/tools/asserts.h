// © 2026 Pawel Mlynarz

#pragma once

#include "core_module.h"
#include "common/types.h"

#include <string>
#include <format>
#include <source_location>

#define PX_TODO(Msg) void(Msg)

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
std::atomic_bool EnsureHasExecuted{false};

constexpr uint64 FileLineHashForEnsure(std::source_location const& Loc = std::source_location::current()) {
    uint32 Result{2166136261u};
    char const* Filename{Loc.file_name()};
    for (; *Filename; ++Filename) {
        Result ^= static_cast<uint8>(*Filename);
        Result *= 16777619u;
    }
    return (static_cast<uint64>(Result) << 32) | Loc.line();
}

inline std::string GetTranslationUnitInfo(std::source_location const& Loc = std::source_location::current()) {
    return std::format("In function {} on line {}", Loc.function_name(), Loc.line());
}

PXCORE_API bool ExecEnsureCheck(bool const bAlways, std::atomic_bool& bExecuted, std::string const& TranslationUnitInfo, std::string const& Message = {});

PXCORE_API bool ExecAssertCheck(std::string const& TranslationUnitInfo, std::string const& Message = {});

} // namespace px::asserts

#if !defined(DO_ENSURE)
#define DO_ENSURE defined(_DEBUG)
#endif

#if !defined(DO_CHECK)
#define DO_CHECK defined(_DEBUG)
#endif

#define PX_ENSURE_IMPL(Always, Expression, ...)                                    \
    (                                                                              \
        !!(Expression) ||                                                          \
        (px::asserts::ExecEnsureCheck(                                             \
             Always,                                                               \
             px::asserts::EnsureHasExecuted<px::asserts::FileLineHashForEnsure()>, \
             px::asserts::GetTranslationUnitInfo(),                                \
             ##__VA_ARGS__                                                         \
         ) &&                                                                      \
         BREAK_AND_RETURN_FALSE()))

#define Ensure(Expression) \
    PX_ENSURE_IMPL(false, Expression)

#define EnsureAlways(Expression) \
    PX_ENSURE_IMPL(true, Expression)

#define EnsureMsgf(Expression, Fmt, ...) \
    PX_ENSURE_IMPL(false, Expression, std::format(Fmt, __VA_ARGS__))

#define EnsureAlwaysMsgf(Expression, Fmt, ...) \
    PX_ENSURE_IMPL(true, Expression, Fmt, __VA_ARGS__)

#define EnsureReturnIfFalse(Condition, ...) \
    if (!(Condition)) {                     \
        Ensure(false);                      \
        return __VA_OPT__(__VA_ARGS__);     \
    }

#define ReturnIfFalse(Condition, ...)   \
    if (!(Condition)) {                 \
        return __VA_OPT__(__VA_ARGS__); \
    }

#define EnsureContinueIfFalse(Condition) \
    if (!(Condition)) {                  \
        Ensure(false);                   \
        continue;                        \
    }

#define ContinueIfFalse(Condition) \
    if (!(Condition)) {            \
        continue;                  \
    }

#define EnsureNoEntry(Fmt, ...) \
    EnsureMsgf(false, Fmt, __VA_ARGS__);

#define PX_ASSERT_IMPL(Expression, ...)                \
    if (!(Expression)) {                               \
        if (px::asserts::ExecAssertCheck(              \
                px::asserts::GetTranslationUnitInfo(), \
                ##__VA_ARGS__                          \
            ))                                         \
            BREAK_AND_ABORT();                         \
    }                                                  \
    (void)0

#define Assert(Expression) PX_ASSERT_IMPL(Expression)

#define AssertMsgf(Expression, Fmt, ...) PX_ASSERT_IMPL(Expression, std::format(Fmt, __VA_ARGS__))
