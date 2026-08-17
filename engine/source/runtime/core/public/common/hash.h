// © 2026 Pawel Mlynarz

#pragma once

#include "types.h"
#include "external/wyhash/wyhash.h"

#include <cstring>
#include <string_view>
#include <type_traits>

namespace px {

using hash_t = uint64;

//////////////////////////////////////////////////////
// Compile Time Hashing

// FNV-1a is used for hashes that must be computed at compile time, such as string identifiers and type
// tags. It is slower than wyhash on large inputs but it is constexpr, which wyhash cannot be as it
// relies on memcpy and platform intrinsics.
//
// Note that FNV-1a and wyhash produce different values for the same input, so a hash must always be
// compared against one produced by the same function.

inline constexpr uint64 kFnv1aOffsetBasis{14695981039346656037ull};
inline constexpr uint64 kFnv1aPrime{1099511628211ull};

/**
 * Hashes a string with the 64 bit FNV-1a algorithm. Usable in constant expressions, which makes it
 * suitable for hashing string literals at compile time.
 *
 * @param str String to hash. Accepts string literals, character pointers and string views.
 * @param hash Hash to continue from, which allows several strings to be hashed as if they were one.
 *
 * @return Hash of the string.
 */
[[nodiscard]]
consteval hash_t hashStringFnv1a(std::string_view const str, uint64 hash = kFnv1aOffsetBasis) noexcept {
    for (char const c : str) {
        hash ^= static_cast<uint64>(static_cast<uint8>(c));
        hash *= kFnv1aPrime;
    }
    return hash;
}

//////////////////////////////////////////////////////
// Runtime Hashing

// Wyhash is used for everything that is hashed at runtime, most notably container keys. It is
// significantly faster than FNV-1a on anything larger than a few bytes.

inline constexpr uint64 kDefaultHashSeed{0};

[[nodiscard]]
inline hash_t hashBytes(void const* const data, size_t const size, uint64 const seed = kDefaultHashSeed) noexcept {
    return detail::wyhash(data, size, seed, detail::_wyp);
}

[[nodiscard]]
inline hash_t hashCombine(uint64 const a, uint64 const b) noexcept {
    return detail::wyhash64(a, b);
}

[[nodiscard]]
inline hash_t hashOf(std::string_view const str, uint64 const seed = kDefaultHashSeed) noexcept {
    return hashBytes(str.data(), str.size(), seed);
}

[[nodiscard]]
inline hash_t hashOf(char const* const str, uint64 const seed = kDefaultHashSeed) noexcept {
    return hashBytes(str, std::strlen(str), seed);
}

template <typename T>
[[nodiscard]]
hash_t hashOf(T const& value, uint64 const seed = kDefaultHashSeed) noexcept {
    if constexpr (std::is_enum_v<T>) {
        return hashOf(static_cast<std::underlying_type_t<T>>(value), seed);
    } else if constexpr (std::is_integral_v<T>) {
        return detail::wyhash64(static_cast<uint64>(value), seed);
    } else if constexpr (std::is_pointer_v<T>) {
        return detail::wyhash64(static_cast<uint64>(reinterpret_cast<uintptr_t>(value)), seed);
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
