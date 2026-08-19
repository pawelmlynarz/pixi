// © 2026 Pawel Mlynarz

#include "common/bitflags.h"

#include <gtest/gtest.h>

#include <iterator>
#include <ranges>
#include <vector>

using namespace px;

namespace bitflags_test {

enum class Permission : uint8 {
    None = 0,
    Read = 1 << 0,
    Write = 1 << 1,
    Execute = 1 << 2,
};

PX_ENABLE_BIT_FLAGS(Permission);

enum class Stage : uint64 {
    None = 0,
    Vertex = 1ull << 0,
    Fragment = 1ull << 1,
    Compute = 1ull << 63,
};

PX_ENABLE_BIT_FLAGS(Stage);

enum class Colour : uint8 { Red, Green, Blue };

} // namespace bitflags_test

namespace outer::inner {

enum class Feature : uint16 {
    None = 0,
    Shadows = 1 << 0,
    Reflections = 1 << 1,
};

PX_ENABLE_BIT_FLAGS(Feature);

struct Settings {
    BitFlags<Feature> Features{Feature::Shadows};
};

} // namespace outer::inner

enum class GlobalFeature : uint8 {
    None = 0,
    First = 1 << 0,
    Second = 1 << 1,
};

PX_ENABLE_BIT_FLAGS(GlobalFeature);

namespace placement {

struct Host {
    enum class Mode : uint8 {
        None = 0,
        Read = 1 << 0,
        Write = 1 << 1,
    };
};

PX_ENABLE_BIT_FLAGS(Host::Mode);

enum class Misplaced : uint8 {
    None = 0,
    Something = 1 << 0,
};

} // namespace placement

PX_ENABLE_BIT_FLAGS(placement::Misplaced);

namespace {

using bitflags_test::Colour;
using bitflags_test::Permission;
using bitflags_test::Stage;

using Permissions = BitFlags<Permission>;
using Stages = BitFlags<Stage>;

template <typename FlagsT>
std::vector<typename FlagsT::EnumType> collect(FlagsT const flags) {
    std::vector<typename FlagsT::EnumType> present;
    for (auto const flag : flags) {
        present.push_back(flag);
    }
    return present;
}

} // namespace

//////////////////////////////////////////////////////
// Opt In

TEST(BitFlags, OnlyOptedInEnumsAreAccepted) {
    static_assert(BitFlagsEnum<Permission>);
    static_assert(BitFlagsEnum<Stage>);

    static_assert(!BitFlagsEnum<Colour>);
    static_assert(!BitFlagsEnum<int>);
    SUCCEED();
}

TEST(BitFlags, OptsInAtGlobalScope) {
    static_assert(BitFlagsEnum<GlobalFeature>);

    BitFlags<GlobalFeature> features{GlobalFeature::First | GlobalFeature::Second};
    EXPECT_EQ(features.count(), 2u);
}

TEST(BitFlags, OptsInForAnEnumNestedInAClass) {
    static_assert(BitFlagsEnum<placement::Host::Mode>);

    BitFlags<placement::Host::Mode> modes{placement::Host::Mode::Read};
    EXPECT_TRUE(modes.has(placement::Host::Mode::Read));
}

TEST(BitFlags, OptInMustLiveInTheEnumsNamespace) {
    static_assert(!BitFlagsEnum<placement::Misplaced>);
    SUCCEED();
}

TEST(BitFlags, OptsInFromANestedNamespace) {
    static_assert(BitFlagsEnum<outer::inner::Feature>);

    outer::inner::Settings settings;
    EXPECT_TRUE(settings.Features.has(outer::inner::Feature::Shadows));

    settings.Features.set(outer::inner::Feature::Reflections);
    EXPECT_EQ(settings.Features.count(), 2u);
}

TEST(BitFlags, UsesAnUnsignedValueTypeOfTheUnderlyingType) {
    static_assert(std::is_same_v<Permissions::ValueType, uint8>);
    static_assert(std::is_same_v<Stages::ValueType, uint64>);
    static_assert(std::is_same_v<Permissions::EnumType, Permission>);
    static_assert(sizeof(Permissions) == sizeof(uint8));
    SUCCEED();
}

//////////////////////////////////////////////////////
// Construction

TEST(BitFlags, DefaultConstructsEmpty) {
    Permissions const flags;
    EXPECT_TRUE(flags.isEmpty());
    EXPECT_EQ(flags.count(), 0u);
    EXPECT_FALSE(static_cast<bool>(flags));
}

TEST(BitFlags, ConstructsFromASingleFlagImplicitly) {
    Permissions const flags{Permission::Read};
    EXPECT_TRUE(flags.has(Permission::Read));
    EXPECT_FALSE(flags.has(Permission::Write));
    EXPECT_EQ(flags.count(), 1u);
}

TEST(BitFlags, ConstructsFromARawValue) {
    Permissions const flags{Permissions::fromValue(0b101)};
    EXPECT_TRUE(flags.has(Permission::Read));
    EXPECT_TRUE(flags.has(Permission::Execute));
    EXPECT_FALSE(flags.has(Permission::Write));
    EXPECT_EQ(flags.value(), 0b101);
}

TEST(BitFlags, DoesNotConvertBackToItsEnumImplicitly) {
    static_assert(std::is_convertible_v<Permission, Permissions>);
    static_assert(!std::is_convertible_v<Permissions, Permission>);
    SUCCEED();
}

//////////////////////////////////////////////////////
// Queries

TEST(BitFlags, HasRequiresEveryRequestedFlag) {
    Permissions const flags{Permission::Read | Permission::Write};
    EXPECT_TRUE(flags.has(Permission::Read));
    EXPECT_TRUE(flags.has(Permission::Read | Permission::Write));
    EXPECT_FALSE(flags.has(Permission::Read | Permission::Execute));
}

TEST(BitFlags, HasAnyRequiresAtLeastOneFlag) {
    Permissions const flags{Permission::Read};
    EXPECT_TRUE(flags.hasAny(Permission::Read | Permission::Execute));
    EXPECT_FALSE(flags.hasAny(Permission::Write | Permission::Execute));
}

TEST(BitFlags, HasNoneIsTheInverseOfHasAny) {
    Permissions const flags{Permission::Read};
    EXPECT_TRUE(flags.hasNone(Permission::Write | Permission::Execute));
    EXPECT_FALSE(flags.hasNone(Permission::Read | Permission::Write));
}

TEST(BitFlags, AnEmptySetIsContainedInEverySet) {
    Permissions const flags{Permission::Read};
    EXPECT_TRUE(flags.has(Permission::None));
    EXPECT_TRUE(Permissions{}.has(Permission::None));
    EXPECT_FALSE(Permissions{}.hasAny(Permission::Read));
}

TEST(BitFlags, CountsThePresentFlags) {
    EXPECT_EQ(Permissions{}.count(), 0u);
    EXPECT_EQ(Permissions{Permission::Read}.count(), 1u);
    EXPECT_EQ(Permissions{Permission::Read | Permission::Write | Permission::Execute}.count(), 3u);
}

//////////////////////////////////////////////////////
// Mutation

TEST(BitFlags, SetAddsFlags) {
    Permissions flags;
    flags.set(Permission::Read).set(Permission::Write);
    EXPECT_TRUE(flags.has(Permission::Read | Permission::Write));
}

TEST(BitFlags, SetIsIdempotent) {
    Permissions flags{Permission::Read};
    flags.set(Permission::Read);
    EXPECT_EQ(flags.count(), 1u);
}

TEST(BitFlags, UnsetRemovesFlags) {
    Permissions flags{Permission::Read | Permission::Write};
    flags.unset(Permission::Read);
    EXPECT_FALSE(flags.has(Permission::Read));
    EXPECT_TRUE(flags.has(Permission::Write));
}

TEST(BitFlags, UnsetOfAnAbsentFlagIsHarmless) {
    Permissions flags{Permission::Read};
    flags.unset(Permission::Write);
    EXPECT_EQ(flags, Permissions{Permission::Read});
}

TEST(BitFlags, ConditionalSetAddsOrRemoves) {
    Permissions flags;
    flags.set(Permission::Read, true);
    EXPECT_TRUE(flags.has(Permission::Read));
    flags.set(Permission::Read, false);
    EXPECT_FALSE(flags.has(Permission::Read));
}

TEST(BitFlags, ToggleFlipsFlags) {
    Permissions flags{Permission::Read};
    flags.toggle(Permission::Read | Permission::Write);
    EXPECT_FALSE(flags.has(Permission::Read));
    EXPECT_TRUE(flags.has(Permission::Write));
}

TEST(BitFlags, ClearRemovesEverything) {
    Permissions flags{Permission::Read | Permission::Write};
    flags.clear();
    EXPECT_TRUE(flags.isEmpty());
}

//////////////////////////////////////////////////////
// Operators

TEST(BitFlags, EnumOperandsProduceASet) {
    Permissions const flags{Permission::Read | Permission::Write};
    EXPECT_EQ(flags.count(), 2u);
    static_assert(std::is_same_v<decltype(Permission::Read | Permission::Write), Permissions>);
}

TEST(BitFlags, MixesSetsAndSingleFlagsOnEitherSide) {
    Permissions const base{Permission::Read};
    EXPECT_EQ(base | Permission::Write, Permission::Read | Permission::Write);
    EXPECT_EQ(Permission::Write | base, Permission::Read | Permission::Write);
}

TEST(BitFlags, IntersectionAndDifference) {
    Permissions const lhs{Permission::Read | Permission::Write};
    Permissions const rhs{Permission::Write | Permission::Execute};
    EXPECT_EQ(lhs & rhs, Permissions{Permission::Write});
    EXPECT_EQ(lhs ^ rhs, Permission::Read | Permission::Execute);
}

TEST(BitFlags, ComplementInvertsMembership) {
    Permissions const flags{~Permissions{Permission::Read}};
    EXPECT_FALSE(flags.has(Permission::Read));
    EXPECT_TRUE(flags.has(Permission::Write));
    EXPECT_TRUE(flags.has(Permission::Execute));
}

TEST(BitFlags, CompoundAssignment) {
    Permissions flags{Permission::Read};
    flags |= Permission::Write;
    EXPECT_EQ(flags, Permission::Read | Permission::Write);

    flags &= Permission::Write;
    EXPECT_EQ(flags, Permissions{Permission::Write});

    flags ^= Permission::Write;
    EXPECT_TRUE(flags.isEmpty());
}

TEST(BitFlags, ComparesForEquality) {
    EXPECT_EQ(Permissions{Permission::Read}, Permissions{Permission::Read});
    EXPECT_NE(Permissions{Permission::Read}, Permissions{Permission::Write});
    EXPECT_EQ(Permissions{Permission::Read}, Permission::Read);
}

//////////////////////////////////////////////////////
// Iteration

TEST(BitFlags, IteratesPresentFlagsFromTheLowestBit) {
    Permissions const flags{Permission::Execute | Permission::Read};
    EXPECT_EQ(collect(flags), (std::vector<Permission>{Permission::Read, Permission::Execute}));
}

TEST(BitFlags, IteratingAnEmptySetYieldsNothing) {
    EXPECT_TRUE(collect(Permissions{}).empty());
}

TEST(BitFlags, IteratesEveryFlag) {
    Permissions const flags{Permission::Read | Permission::Write | Permission::Execute};
    EXPECT_EQ(
        collect(flags),
        (std::vector<Permission>{Permission::Read, Permission::Write, Permission::Execute})
    );
}

TEST(BitFlags, HandlesTheHighestBitOfAWideUnderlyingType) {
    Stages const stages{Stage::Vertex | Stage::Compute};
    EXPECT_TRUE(stages.has(Stage::Compute));
    EXPECT_EQ(stages.count(), 2u);
    EXPECT_EQ(collect(stages), (std::vector<Stage>{Stage::Vertex, Stage::Compute}));
}

TEST(BitFlags, IteratorSatisfiesTheStandardConcepts) {
    static_assert(std::input_iterator<Permissions::Iterator>);
    static_assert(std::ranges::input_range<Permissions>);
    static_assert(std::sentinel_for<Permissions::Iterator, Permissions::Iterator>);
    SUCCEED();
}

TEST(BitFlags, WorksWithRangeAlgorithms) {
    Permissions const flags{Permission::Read | Permission::Execute};
    EXPECT_EQ(std::ranges::distance(flags), 2);
    EXPECT_NE(std::ranges::find(flags, Permission::Execute), flags.end());
    EXPECT_EQ(std::ranges::find(flags, Permission::Write), flags.end());
}

//////////////////////////////////////////////////////
// Constant Expressions

TEST(BitFlags, IsUsableInConstantExpressions) {
    constexpr Permissions flags{Permission::Read | Permission::Write};
    static_assert(flags.has(Permission::Read));
    static_assert(!flags.has(Permission::Execute));
    static_assert(flags.count() == 2u);
    static_assert(flags.value() == 0b011);
    static_assert((flags & Permission::Read) == Permissions{Permission::Read});
    static_assert(Permissions{}.isEmpty());
    SUCCEED();
}
