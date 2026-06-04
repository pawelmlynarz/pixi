// � 2026 Pawel Mlynarz

#include "common/windows/windows_platform_time.h"

namespace px {

namespace {

LARGE_INTEGER Frequency;

inline int64 SafeInt64MulDiv(int64 const Value, int64 const Numer, int64 const Denom) {
    int64 const Q{Value / Denom};
    int64 const R{Value % Denom};
    return Q * Numer + R * Numer / Denom;
}

} // namespace

void WindowsPlatformTime::Initialize() {
    QueryPerformanceFrequency(&Frequency);
}

void WindowsPlatformTime::Shutdown() {
}

TimePoint WindowsPlatformTime::Now() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);

    int64 constexpr MicrosecondsPerSecond{1000000LL};
    TimePoint const Microseconds{SafeInt64MulDiv(time.QuadPart, MicrosecondsPerSecond, Frequency.QuadPart)};

    return Microseconds;
}

TimePoint WindowsPlatformTime::From(TimePoint StartingTime) {
    return Now() - StartingTime;
}

TimePoint WindowsPlatformTime::Delta(TimePoint StartingTime, TimePoint EndingTime) {
    return EndingTime - StartingTime;
}

} // namespace px
