// � 2026 Pawel Mlynarz

#include "platform/windows/windows_platform_time.h"

#include "Windows.h"

namespace px {

namespace {

LARGE_INTEGER Frequency;

inline int64 SafeInt64MulDiv(int64 const Value, int64 const Numer, int64 const Denom) {
    int64 const Q{Value / Denom};
    int64 const R{Value % Denom};
    return (Q * Numer) + (R * Numer / Denom);
}

} // namespace

TimePoint WindowsPlatformTime::Initialize() noexcept {
    QueryPerformanceFrequency(&Frequency);
    return Now();
}

TimePoint WindowsPlatformTime::Now() {
    LARGE_INTEGER Time;
    QueryPerformanceCounter(&Time);

    int64 constexpr MicrosecondsPerSecond{1000000LL};
    TimePoint const Microseconds{SafeInt64MulDiv(Time.QuadPart, MicrosecondsPerSecond, Frequency.QuadPart)};

    return Microseconds;
}

TimePoint WindowsPlatformTime::From(TimePoint StartingTime) {
    return Now() - StartingTime;
}

TimePoint WindowsPlatformTime::Delta(TimePoint StartingTime, TimePoint EndingTime) {
    return EndingTime - StartingTime;
}

} // namespace px
