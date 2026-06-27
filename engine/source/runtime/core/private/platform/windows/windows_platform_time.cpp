// � 2026 Pawel Mlynarz

#include "platform/windows/windows_platform_time.h"

#include "Windows.h"

namespace px {

namespace {

LARGE_INTEGER frequency;

int64 safeInt64MulDiv(int64 const value, int64 const numer, int64 const denom) {
    int64 const q{value / denom};
    int64 const r{value % denom};
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

    int64 constexpr microsecondsPerSecond{1000000LL};
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
