// © 2026 Pawel Mlynarz

#pragma once

#include "common/types.h"

#include <bit>
#include <iterator>
#include <type_traits>

namespace px {

//////////////////////////////////////////////////////
// Opt In

template <typename EnumT>
    requires std::is_enum_v<EnumT>
constexpr bool pxEnableBitFlags(EnumT) noexcept {
    return false;
}

template <typename EnumT>
concept BitFlagsEnum = std::is_enum_v<EnumT> && pxEnableBitFlags(EnumT{});

//////////////////////////////////////////////////////
// Bit Flags

template <BitFlagsEnum EnumT>
class BitFlags {
  public:
    using EnumType = EnumT;
    using ValueType = std::make_unsigned_t<std::underlying_type_t<EnumT>>;

  public:
    class Iterator {
      public:
        using value_type = EnumT;
        using difference_type = ptrdiff_t;
        using iterator_concept = std::input_iterator_tag;
        using iterator_category = std::input_iterator_tag;

        constexpr Iterator() noexcept = default;

        constexpr explicit Iterator(ValueType const bits) noexcept
            : bits_(bits) {
        }

        constexpr EnumT operator*() const noexcept {
            return static_cast<EnumT>(lowestBit(bits_));
        }

        constexpr Iterator& operator++() noexcept {
            bits_ = withoutLowestBit(bits_);
            return *this;
        }

        constexpr Iterator operator++(int) noexcept {
            Iterator const previous{*this};
            ++(*this);
            return previous;
        }

        friend constexpr bool operator==(Iterator const lhs, Iterator const rhs) noexcept {
            return lhs.bits_ == rhs.bits_;
        }

      private:
        ValueType bits_{0};
    };

    //////////////////////////////////////////////////////
    // Construction

    constexpr BitFlags() noexcept = default;

    constexpr BitFlags(EnumT const flag) noexcept
        : bits_(toBits(flag)) {
    }

    static constexpr BitFlags fromValue(ValueType const bits) noexcept {
        BitFlags flags;
        flags.bits_ = bits;
        return flags;
    }

    //////////////////////////////////////////////////////
    // Queries

    [[nodiscard]]
    constexpr bool has(BitFlags const flags) const noexcept {
        return (bits_ & flags.bits_) == flags.bits_;
    }

    [[nodiscard]]
    constexpr bool hasAny(BitFlags const flags) const noexcept {
        return (bits_ & flags.bits_) != 0;
    }

    [[nodiscard]]
    constexpr bool hasNone(BitFlags const flags) const noexcept {
        return (bits_ & flags.bits_) == 0;
    }

    [[nodiscard]]
    constexpr bool isEmpty() const noexcept {
        return bits_ == 0;
    }

    [[nodiscard]]
    constexpr u32 count() const noexcept {
        return static_cast<u32>(std::popcount(bits_));
    }

    [[nodiscard]]
    constexpr ValueType value() const noexcept {
        return bits_;
    }

    [[nodiscard]]
    constexpr explicit operator bool() const noexcept {
        return bits_ != 0;
    }

    //////////////////////////////////////////////////////
    // Mutation

    constexpr BitFlags& set(BitFlags const flags) noexcept {
        bits_ = static_cast<ValueType>(bits_ | flags.bits_);
        return *this;
    }

    constexpr BitFlags& set(BitFlags const flags, bool const enabled) noexcept {
        return enabled ? set(flags) : unset(flags);
    }

    constexpr BitFlags& unset(BitFlags const flags) noexcept {
        bits_ = static_cast<ValueType>(bits_ & ~flags.bits_);
        return *this;
    }

    constexpr BitFlags& toggle(BitFlags const flags) noexcept {
        bits_ = static_cast<ValueType>(bits_ ^ flags.bits_);
        return *this;
    }

    constexpr BitFlags& clear() noexcept {
        bits_ = 0;
        return *this;
    }

    //////////////////////////////////////////////////////
    // Iteration

    [[nodiscard]]
    constexpr Iterator begin() const noexcept {
        return Iterator{bits_};
    }

    [[nodiscard]]
    constexpr Iterator end() const noexcept {
        return Iterator{0};
    }

    //////////////////////////////////////////////////////
    // Operators

    constexpr BitFlags& operator|=(BitFlags const rhs) noexcept { return set(rhs); }
    constexpr BitFlags& operator&=(BitFlags const rhs) noexcept {
        bits_ = static_cast<ValueType>(bits_ & rhs.bits_);
        return *this;
    }
    constexpr BitFlags& operator^=(BitFlags const rhs) noexcept { return toggle(rhs); }

    [[nodiscard]]
    constexpr BitFlags operator~() const noexcept {
        return fromValue(static_cast<ValueType>(~bits_));
    }

    [[nodiscard]]
    friend constexpr BitFlags operator|(BitFlags const lhs, BitFlags const rhs) noexcept {
        return fromValue(static_cast<ValueType>(lhs.bits_ | rhs.bits_));
    }

    [[nodiscard]]
    friend constexpr BitFlags operator&(BitFlags const lhs, BitFlags const rhs) noexcept {
        return fromValue(static_cast<ValueType>(lhs.bits_ & rhs.bits_));
    }

    [[nodiscard]]
    friend constexpr BitFlags operator^(BitFlags const lhs, BitFlags const rhs) noexcept {
        return fromValue(static_cast<ValueType>(lhs.bits_ ^ rhs.bits_));
    }

    [[nodiscard]]
    friend constexpr bool operator==(BitFlags const lhs, BitFlags const rhs) noexcept {
        return lhs.bits_ == rhs.bits_;
    }

  private:
    static constexpr ValueType toBits(EnumT const flag) noexcept {
        return static_cast<ValueType>(flag);
    }

    static constexpr ValueType lowestBit(ValueType const bits) noexcept {
        return static_cast<ValueType>(bits & (~bits + ValueType{1}));
    }

    static constexpr ValueType withoutLowestBit(ValueType const bits) noexcept {
        return static_cast<ValueType>(bits & (bits - ValueType{1}));
    }

  private:
    ValueType bits_{0};
};

//////////////////////////////////////////////////////
// Enum Operators

template <BitFlagsEnum EnumT>
[[nodiscard]]
constexpr BitFlags<EnumT> operator|(EnumT const lhs, EnumT const rhs) noexcept {
    return BitFlags<EnumT>{lhs} | BitFlags<EnumT>{rhs};
}

template <BitFlagsEnum EnumT>
[[nodiscard]]
constexpr BitFlags<EnumT> operator&(EnumT const lhs, EnumT const rhs) noexcept {
    return BitFlags<EnumT>{lhs} & BitFlags<EnumT>{rhs};
}

template <BitFlagsEnum EnumT>
[[nodiscard]]
constexpr BitFlags<EnumT> operator^(EnumT const lhs, EnumT const rhs) noexcept {
    return BitFlags<EnumT>{lhs} ^ BitFlags<EnumT>{rhs};
}

template <BitFlagsEnum EnumT>
[[nodiscard]]
constexpr BitFlags<EnumT> operator~(EnumT const flag) noexcept {
    return ~BitFlags<EnumT>{flag};
}

} // namespace px

#define PX_ENABLE_BIT_FLAGS(EnumType)                     \
    constexpr bool pxEnableBitFlags(EnumType) noexcept {  \
        return true;                                      \
    }
