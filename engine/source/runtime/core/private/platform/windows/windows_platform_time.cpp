// � 2026 Pawel Mlynarz

#include "platform/windows/windows_platform_time.h"

#include "Windows.h"

namespace px {

namespace {

LARGE_INTEGER frequency;

i64 safeInt64MulDiv(i64 const value, i64 const numer, i64 const denom) {
    i64 const q{value / denom};
    i64 const r{value % denom};
    return (q * numer) + (r * numer / denom);
}

} // namespace

TimePoint WindowsPlatformTime::initialize() noexcept {
    QueryPerformanceFrequency(&frequency);
    return now();
}

TimePoint WindowsPlatformTime::now() {
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);

    i64 constexpr microsecondsPerSecond{1000000LL};
    TimePoint const microseconds{safeInt64MulDiv(time.QuadPart, microsecondsPerSecond, frequency.QuadPart)};

    return microseconds;
}

TimePoint WindowsPlatformTime::from(TimePoint startingTime) {
    return now() - startingTime;
}

TimePoint WindowsPlatformTime::delta(TimePoint startingTime, TimePoint endingTime) {
    return endingTime - startingTime;
}

} // namespace px
