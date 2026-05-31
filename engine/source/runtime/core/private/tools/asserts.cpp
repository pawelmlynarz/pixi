// © 2026 Pawel Mlynarz

#include "tools/asserts.h"

#include "common/platform.h"

#include <print>

namespace px::asserts {

bool ExecEnsureCheck(bool const bAlways, std::atomic_bool& bExecuted, [[maybe_unused]] std::string const& TranslationUnitInfo, std::string const& Message) {
    if (bAlways || !bExecuted.load(std::memory_order_relaxed)) {
        if (!bAlways) {
            bExecuted.store(true, std::memory_order_release);
        }
        std::string const Msg{std::format("[Ensure condition failed].\n{}\n{}", TranslationUnitInfo, Message.empty() ? "" : std::format("Message: {}\n", Message))};

        PX_TODO("Logger");
        (void)fprintf(stderr, "%s", Msg.c_str());
#if PLATFORM_WINDOWS
        OutputDebugStringA(Msg.c_str());
#endif

        return IsDebuggerPresent(); // Proceed to DEBUG_BREAK
    }
    return false;
}

PXCORE_API bool ExecAssertCheck(std::string const& TranslationUnitInfo, std::string const& Message) {
    std::string const Msg{std::format("[Assert Failure].\n{}\n{}", TranslationUnitInfo, Message.empty() ? "" : std::format("Message: {}\n", Message))};

    PX_TODO("Logger");
    (void)fprintf(stderr, "%s", Msg.c_str());
#if PLATFORM_WINDOWS
    OutputDebugStringA(Msg.c_str());
#endif

    return true; // Proceed to Abort
}

} // namespace px::asserts
