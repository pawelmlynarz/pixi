// © 2026 Pawel Mlynarz

#include "tools/asserts.h"

#if PLATFORM_WINDOWS
#include "Windows.h"
#endif
#include <print>

namespace px::asserts {

bool execEnsureCheck(bool const bAlways, std::atomic_bool& bExecuted, [[maybe_unused]] std::string const& translationUnitInfo, std::string const& message) {
    if (bAlways || !bExecuted.load(std::memory_order_relaxed)) {
        if (!bAlways) {
            bExecuted.store(true, std::memory_order_release);
        }
        std::string const msg{std::format("[Ensure condition failed].\n{}\n{}", translationUnitInfo, message.empty() ? "" : std::format("Message: {}\n", message))};

        pxToDo("Logger");
        (void)fprintf(stderr, "%s", msg.c_str());
#if PLATFORM_WINDOWS
        OutputDebugStringA(msg.c_str());
#endif

        return IsDebuggerPresent(); // Proceed to DEBUG_BREAK
    }
    return false;
}

PXCORE_API bool execAssertCheck(std::string const& translationUnitInfo, std::string const& message) {
    std::string const msg{std::format("[Assert Failure].\n{}\n{}", translationUnitInfo, message.empty() ? "" : std::format("Message: {}\n", message))};

    pxToDo("Logger");
    (void)fprintf(stderr, "%s", msg.c_str());
#if PLATFORM_WINDOWS
    OutputDebugStringA(msg.c_str());
#endif

    return true; // Proceed to Abort
}

} // namespace px::asserts
