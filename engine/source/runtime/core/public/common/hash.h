// © 2026 Pawel Mlynarz

#pragma once

#include "types.h"
#include "external/wyhash/wyhash.h"

#include <cstring>
#include <string_view>
#include <type_traits>

namespace px {

using hash_t = u64;

//////////////////////////////////////////////////////
// Compile Time Hashing

// FNV-1a is used for hashes that must be computed at compile time, such as string identifiers and type
// tags. Note that FNV-1a and wyhash produce different values for the same input, so a hash must always be
// compared against one produced by the same function.

inline constexpr u64 kFnv1aOffsetBasis{14695981039346656037ull};
inline constexpr u64 kFnv1aPrime{1099511628211ull};

[[nodiscard]]
consteval hash_t hashStringFnv1a(std::string_view const str, u64 hash = kFnv1aOffsetBasis) noexcept {
    for (char const c : str) {
        hash ^= static_cast<u64>(static_cast<u8>(c));
        hash *= kFnv1aPrime;
    }
    return hash;
}

//////////////////////////////////////////////////////
// Runtime Hashing

inline constexpr u64 kDefaultHashSeed{0};

[[nodiscard]]
inline hash_t hashBytes(void const* const data, size_t const size, u64 const seed = kDefaultHashSeed) noexcept {
    return detail::wyhash(data, size, seed, detail::_wyp);
}

[[nodiscard]]
inline hash_t hashCombine(u64 const a, u64 const b) noexcept {
    return detail::wyhash64(a, b);
}

[[nodiscard]]
inline hash_t hashOf(std::string_view const str, u64 const seed = kDefaultHashSeed) noexcept {
    return hashBytes(str.data(), str.size(), seed);
}

[[nodiscard]]
inline hash_t hashOf(cstring const str, u64 const seed = kDefaultHashSeed) noexcept {
    return hashBytes(str, std::strlen(str), seed);
}

template <typename T>
    requires(!std::is_convertible_v<T const&, std::string_view>)
[[nodiscard]]
hash_t hashOf(T const& value, u64 const seed = kDefaultHashSeed) noexcept {
    if constexpr (std::is_enum_v<T>) {
        return hashOf(static_cast<std::underlying_type_t<T>>(value), seed);
    } else if constexpr (std::is_integral_v<T>) {
        return detail::wyhash64(static_cast<u64>(value), seed);
    } else if constexpr (std::is_pointer_v<T>) {
        return detail::wyhash64(static_cast<u64>(reinterpret_cast<uintptr_t>(value)), seed);
    } else {
        static_assert(std::is_trivially_copyable_v<T>, "Only trivially copyable types can be hashed by their object representation.");
        static_assert(
            std::has_unique_object_representations_v<T>,
            "Type contains padding or a non unique representation, so equal values could hash differently. Provide a hashOf overload for it."
        );
        return hashBytes(&value, sizeof(T), seed);
    }
}

} // namespace px
