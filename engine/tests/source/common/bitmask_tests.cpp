// © 2026 Pawel Mlynarz

#include "common/bitmask.h"

#include <gtest/gtest.h>

#include <vector>

using namespace px;

namespace {

// One bit per slot, as produced by _mm_movemask_epi8.
using SseMask = BitMask<uint32, 16>;

// One byte per slot, as produced by the portable group.
using SwarMask = BitMask<uint64, 8, 3>;

/** Collects the slot indexes yielded by iterating a mask. */
template <typename MaskT>
std::vector<uint32> collect(MaskT const mask) {
    std::vector<uint32> indexes;
    for (uint32 const index : mask) {
        indexes.push_back(index);
    }
    return indexes;
}

} // namespace

//////////////////////////////////////////////////////
// Bit Utilities

TEST(BitUtilities, LeadingZeroes) {
    EXPECT_EQ(leadingZeroes(uint32{0x80000000}), 0u);
    EXPECT_EQ(leadingZeroes(uint32{0x00000001}), 31u);
    EXPECT_EQ(leadingZeroes(uint32{0}), 32u);
    EXPECT_EQ(leadingZeroes(uint64{1}), 63u);
}

TEST(BitUtilities, TrailingZeros) {
    EXPECT_EQ(trailingZeros(uint32{0x00000001}), 0u);
    EXPECT_EQ(trailingZeros(uint32{0x00000100}), 8u);
    EXPECT_EQ(trailingZeros(uint32{0}), 32u);
    EXPECT_EQ(trailingZeros(uint64{1ull << 40}), 40u);
}

TEST(BitUtilities, RoundUpToPowerOf2) {
    EXPECT_EQ(roundUpToPowerOf2(0u), 1u);
    EXPECT_EQ(roundUpToPowerOf2(1u), 1u);
    EXPECT_EQ(roundUpToPowerOf2(3u), 4u);
    EXPECT_EQ(roundUpToPowerOf2(16u), 16u);
    EXPECT_EQ(roundUpToPowerOf2(17u), 32u);
}

TEST(BitUtilities, AreUsableInConstantExpressions) {
    static_assert(leadingZeroes(uint32{0x00000001}) == 31u);
    static_assert(trailingZeros(uint32{0x00000100}) == 8u);
    static_assert(roundUpToPowerOf2(17u) == 32u);
    SUCCEED();
}

//////////////////////////////////////////////////////
// Iteration

TEST(BitMask, IteratesSetBitsLowestFirst) {
    // The example documented on the class: one bit per slot.
    EXPECT_EQ(collect(SseMask{0x5}), (std::vector<uint32>{0, 2}));
}

TEST(BitMask, IteratesByteMarkersWhenShifted) {
    // The example documented on the class: one byte per slot, marker at bit 8 * slot + 7.
    EXPECT_EQ(collect(SwarMask{0x0000000080800000ull}), (std::vector<uint32>{2, 3}));
}

TEST(BitMask, EmptyMaskYieldsNothing) {
    EXPECT_TRUE(collect(SseMask{0}).empty());
    EXPECT_TRUE(collect(SwarMask{0}).empty());
}

TEST(BitMask, IteratesEverySlot) {
    std::vector<uint32> expected;
    for (uint32 slot{0}; slot < 16; ++slot) {
        expected.push_back(slot);
    }
    EXPECT_EQ(collect(SseMask{0xFFFF}), expected);
}

TEST(BitMask, EachSingleSlotYieldsItsOwnIndex) {
    for (uint32 slot{0}; slot < 16; ++slot) {
        EXPECT_EQ(collect(SseMask{uint32{1} << slot}), std::vector<uint32>{slot}) << "slot " << slot;
    }
}

TEST(BitMask, ConvertsToBool) {
    EXPECT_FALSE(static_cast<bool>(SseMask{0}));
    EXPECT_TRUE(static_cast<bool>(SseMask{0x4}));
}

//////////////////////////////////////////////////////
// Bit Queries

TEST(BitMask, LowestAndHighestBitSet) {
    SseMask const mask{0x0102};
    EXPECT_EQ(mask.lowestBitSet(), 1u);
    EXPECT_EQ(mask.highestBitSet(), 8u);
    EXPECT_EQ(*mask, mask.lowestBitSet());
}

TEST(BitMask, TrailingZerosCountsEmptySlotsBelowLowestSetBit) {
    EXPECT_EQ(SseMask{0x0001}.trailingZeros(), 0u);
    EXPECT_EQ(SseMask{0x0100}.trailingZeros(), 8u);
    EXPECT_EQ(SseMask{0x8000}.trailingZeros(), 15u);
}

TEST(BitMask, LeadingZerosIgnoresUnusedHighBits) {
    EXPECT_EQ(SseMask{0x8000}.leadingZeros(), 0u);
    EXPECT_EQ(SseMask{0x4000}.leadingZeros(), 1u);
    EXPECT_EQ(SseMask{0x0001}.leadingZeros(), 15u);
}

TEST(BitMask, BitQueriesAreExpressedInSlotsWhenShifted) {
    SwarMask const highest{0x8000000000000000ull};
    EXPECT_EQ(highest.trailingZeros(), 7u);
    EXPECT_EQ(highest.leadingZeros(), 0u);
    EXPECT_EQ(highest.lowestBitSet(), 7u);
    EXPECT_EQ(highest.highestBitSet(), 7u);

    SwarMask const lowest{0x0000000000000080ull};
    EXPECT_EQ(lowest.trailingZeros(), 0u);
    EXPECT_EQ(lowest.leadingZeros(), 7u);
}

TEST(BitMask, LeadingAndTrailingZerosAreConsistent) {
    for (uint32 slot{0}; slot < 16; ++slot) {
        SseMask const mask{uint32{1} << slot};
        EXPECT_EQ(mask.trailingZeros() + mask.leadingZeros(), 15u) << "slot " << slot;
    }
}
