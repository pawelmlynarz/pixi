// © 2026 Pawel Mlynarz

#pragma once

constexpr std::size_t operator"" _B(unsigned long long const n) {
    return n;
}

constexpr std::size_t operator"" _KiB(unsigned long long const n) {
    return n * 1024ull;
}

constexpr std::size_t operator"" _MiB(unsigned long long const n) {
    return n * 1024ull * 1024ull;
}

constexpr std::size_t operator"" _GiB(unsigned long long const n) {
    return n * 1024ull * 1024ull * 1024ull;
}
