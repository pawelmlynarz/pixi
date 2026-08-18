// © 2026 Pawel Mlynarz

#pragma once

#include "types.h"

#include <bit>
#include <type_traits>

namespace px {

//////////////////////////////////////////////////////
// Utility Methods

constexpr uint32 leadingZeroes(auto const x) noexcept {
    static_assert(std::is_unsigned<decltype(x)>::value);
    return static_cast<uint32>(std::countl_zero(x));
}

constexpr uint32 trailingZeros(auto const x) noexcept {
    static_assert(std::is_unsigned<decltype(x)>::value);
    return static_cast<uint32>(std::countr_zero(x));
}

constexpr uint32 roundUpToPowerOf2(uint32 const value) noexcept {
    return std::bit_ceil(value);
}

//////////////////////////////////////////////////////

/**
 * An abstraction over a bitmask that provides an easy way to iterate through the indexes of its set
 * bits, lowest first. Iteration is allocation free: the mask acts as its own iterator, dereferencing
 * yields the index of the lowest set bit, and incrementing clears that bit.
 *
 * Shift describes how many bits of the mask represent a single slot, and exists because the group
 * implementations backing this mask produce different bit densities:
 *
 *  - Shift = 0 - one bit per slot. This is a true bitmask, as produced on platforms with SSE where
 *    _mm_movemask_epi8 packs the high bit of each of the 16 bytes into a 16 bit value, so bit i maps
 *    directly onto slot i.
 *
 *  - Shift = 3 - one byte per slot. On platforms without SSE the arithmetic used to emulate the SSE
 *    behaviour works in bytes and leaves each byte as either 0x00 or 0x80, so the marker for slot i
 *    sits at bit 8 * i + 7 and the raw bit position has to be divided by eight to recover the index.
 *
 * For example:
 *   for (uint32 i : BitMask<uint32, 16>(0x5)) -> yields 0, 2
 *   for (uint32 i : BitMask<uint64, 8, 3>(0x0000000080800000)) -> yields 2, 3
 */
template <class T, uint32 SignificantBits, uint32 Shift = 0>
class BitMask {
    static_assert(std::is_unsigned<T>::value);
    static_assert(Shift == 0 || Shift == 3);
    static_assert((SignificantBits << Shift) <= sizeof(T) * 8);

    /** Number of mask bits that carry slot information. */
    static constexpr uint32 totalSignificantBits_{SignificantBits << Shift};

    /** Number of unused high bits in the underlying type. */
    static constexpr uint32 extraBits_{static_cast<uint32>(sizeof(T) * 8) - totalSignificantBits_};

  public:
    explicit BitMask(T const mask)
        : mask_(mask) {
    }

    BitMask& operator++() {
        mask_ &= (mask_ - 1);
        return *this;
    }

    explicit operator bool() const noexcept { return mask_ != 0; }

    uint32 operator*() const noexcept { return lowestBitSet(); }

    uint32 lowestBitSet() const noexcept { return trailingZeros(); }

    uint32 highestBitSet() const noexcept {
        return static_cast<uint32>(std::bit_width(mask_) - 1) >> Shift;
    }

    uint32 trailingZeros() const noexcept {
        return px::trailingZeros(mask_) >> Shift;
    }

    uint32 leadingZeros() const noexcept {
        return px::leadingZeroes(static_cast<T>(mask_ << extraBits_)) >> Shift;
    }

    BitMask begin() const noexcept { return *this; }

    BitMask end() const noexcept { return BitMask(0); }

  private:
    friend bool operator==(BitMask const& a, BitMask const& b) {
        return a.mask_ == b.mask_;
    }
    friend bool operator!=(BitMask const& a, BitMask const& b) {
        return a.mask_ != b.mask_;
    }

    T mask_;
};

} // namespace px
