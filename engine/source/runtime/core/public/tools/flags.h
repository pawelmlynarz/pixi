// © 2026 Pawel Mlynarz

#pragma once

#include <type_traits>

// NOLINTBEGIN

template <typename E>
struct EnableBitmaskOperators : std::false_type {};

template <typename E>
inline constexpr bool EnableBitmaskOperators_v =
    EnableBitmaskOperators<E>::value;

template <typename E>
concept BitmaskEnum =
    std::is_enum_v<E> &&
    EnableBitmaskOperators_v<E>;

template <BitmaskEnum E>
constexpr E operator|(E Lhs, E Rhs) noexcept {
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        static_cast<U>(Lhs) | static_cast<U>(Rhs)
    );
}

template <BitmaskEnum E>
constexpr E operator&(E Lhs, E Rhs) noexcept {
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        static_cast<U>(Lhs) & static_cast<U>(Rhs)
    );
}

template <BitmaskEnum E>
constexpr E operator^(E Lhs, E Rhs) noexcept {
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        static_cast<U>(Lhs) ^ static_cast<U>(Rhs)
    );
}

template <BitmaskEnum E>
constexpr E operator~(E Value) noexcept {
    using U = std::underlying_type_t<E>;
    return static_cast<E>(
        ~static_cast<U>(Value)
    );
}

template <BitmaskEnum E>
constexpr E& operator|=(E& Lhs, E Rhs) noexcept {
    return Lhs = Lhs | Rhs;
}

template <BitmaskEnum E>
constexpr E& operator&=(E& Lhs, E Rhs) noexcept {
    return Lhs = Lhs & Rhs;
}

template <BitmaskEnum E>
constexpr E& operator^=(E& Lhs, E Rhs) noexcept {
    return Lhs = Lhs ^ Rhs;
}

#define BitmaskEnum(EnumClass) \
    ;                          \
    template <>                \
    struct EnableBitmaskOperators<EnumClass> : std::true_type {};

namespace px {

template <BitmaskEnum E>
constexpr void SetFlagOn(E& Value, E Flag) noexcept {
    Value |= Flag;
}

template <BitmaskEnum E>
constexpr void SetFlagOff(E& Value, E Flag) noexcept {
    Value &= ~(Flag);
}

template <BitmaskEnum E>
constexpr bool HasFlag(E Value, E Flag) noexcept {
    return static_cast<bool>(Value & Flag);
}

template <BitmaskEnum E>
constexpr bool AreAllFlagsOn(E Falue, E Flags) noexcept {
    return (Falue & Flags) == Flags;
}

template <BitmaskEnum E>
constexpr bool IsAnyFlagOn(E& Value, E Flag) noexcept {
    return static_cast<int32_t>((Value) & (Flag)) != 0;
}

template <BitmaskEnum E>
constexpr void ToggleFlag(E& Value, E Flag) noexcept {
    Value ^= Flag;
}

} // namespace px

// NOLINTEND
