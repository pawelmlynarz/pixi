// © 2026 Pawel Mlynarz

#include "common/hash.h"

#include <gtest/gtest.h>

#include <array>
#include <set>
#include <string>

using namespace px;

namespace {

enum class Backend : uint8 { Vulkan, D3D12 };

struct PackedHandle {
    uint32 index;
    uint32 generation;
};

} // namespace

//////////////////////////////////////////////////////
// Compile Time Hashing

TEST(HashFnv1a, MatchesKnownVectors) {
    static_assert(hashStringFnv1a("") == 0xcbf29ce484222325ull);
    static_assert(hashStringFnv1a("a") == 0xaf63dc4c8601ec8cull);
    static_assert(hashStringFnv1a("foobar") == 0x85944171f73967e8ull);
    SUCCEED();
}

TEST(HashFnv1a, IsEvaluatedAtCompileTime) {
    constexpr hash_t meshTag{hashStringFnv1a("StaticMesh")};
    static_assert(meshTag != 0);

    std::array<int, (meshTag & 0x7) + 1> const usableAsConstant{};
    EXPECT_GE(usableAsConstant.size(), 1u);
}

TEST(HashFnv1a, IsDeterministicAndDistinct) {
    static_assert(hashStringFnv1a("StaticMesh") == hashStringFnv1a("StaticMesh"));
    static_assert(hashStringFnv1a("StaticMesh") != hashStringFnv1a("SkeletalMesh"));
    static_assert(hashStringFnv1a("ab") != hashStringFnv1a("ba"));
    SUCCEED();
}

TEST(HashFnv1a, ChainingMatchesHashingTheConcatenation) {
    static_assert(hashStringFnv1a("bar", hashStringFnv1a("foo")) == hashStringFnv1a("foobar"));
    SUCCEED();
}

TEST(HashFnv1a, DiffersFromRuntimeHash) {
    constexpr hash_t compileTime{hashStringFnv1a("StaticMesh")};
    EXPECT_NE(compileTime, hashOf("StaticMesh"));
}

//////////////////////////////////////////////////////
// Runtime Hashing

TEST(HashBytes, IsDeterministic) {
    char const data[]{"the quick brown fox"};
    EXPECT_EQ(hashBytes(data, sizeof(data)), hashBytes(data, sizeof(data)));
}

TEST(HashBytes, DiffersForDifferentContent) {
    EXPECT_NE(hashBytes("abc", 3), hashBytes("abd", 3));
}

TEST(HashBytes, DiffersForDifferentLength) {
    EXPECT_NE(hashBytes("abc", 3), hashBytes("abc", 2));
}

TEST(HashBytes, RespectsSeed) {
    EXPECT_NE(hashBytes("abc", 3, 0), hashBytes("abc", 3, 1));
}

TEST(HashBytes, HandlesEmptyAndLongInputs) {
    EXPECT_NO_FATAL_FAILURE((void) hashBytes("", 0));

    // Exercises the bulk path of wyhash, which is only taken beyond 48 bytes.
    std::string const large(1024, 'x');
    std::string larger{large};
    larger.push_back('y');
    EXPECT_NE(hashBytes(large.data(), large.size()), hashBytes(larger.data(), larger.size()));
}

//////////////////////////////////////////////////////
// Typed Hashing

TEST(HashOf, StringsHashByContent) {
    std::string const owned{"StaticMesh"};
    std::string_view const view{owned};
    char const* const pointer{owned.c_str()};

    EXPECT_EQ(hashOf(view), hashOf(pointer));
    EXPECT_EQ(hashOf(view), hashOf("StaticMesh"));
    EXPECT_NE(hashOf(view), hashOf("SkeletalMesh"));
}

TEST(HashOf, StdStringHashesByContent) {
    std::string const owned{"StaticMesh"};
    EXPECT_EQ(hashOf(owned), hashOf(std::string_view{"StaticMesh"}));
    EXPECT_EQ(hashOf(std::string{"asset_1"}), hashOf("asset_1"));
}

TEST(HashOf, StringLiteralDoesNotHashItsTerminator) {
    EXPECT_EQ(hashOf("abc"), hashBytes("abc", 3));
}

TEST(HashOf, IntegersAreDeterministicAndDistinct) {
    EXPECT_EQ(hashOf(42), hashOf(42));
    EXPECT_NE(hashOf(42), hashOf(43));
    EXPECT_NE(hashOf(uint64{0}), hashOf(uint64{1}));
}

TEST(HashOf, IntegersRespectSeed) {
    EXPECT_NE(hashOf(42, 0), hashOf(42, 1));
}

TEST(HashOf, EnumsHashAsTheirUnderlyingValue) {
    EXPECT_EQ(hashOf(Backend::D3D12), hashOf(static_cast<uint8>(Backend::D3D12)));
    EXPECT_NE(hashOf(Backend::Vulkan), hashOf(Backend::D3D12));
}

TEST(HashOf, PointersHashByAddress) {
    int values[2]{};
    EXPECT_EQ(hashOf(&values[0]), hashOf(&values[0]));
    EXPECT_NE(hashOf(&values[0]), hashOf(&values[1]));
    EXPECT_EQ(hashOf(static_cast<int*>(nullptr)), hashOf(static_cast<int*>(nullptr)));
}

TEST(HashOf, TriviallyCopyableTypesHashByRepresentation) {
    EXPECT_EQ(hashOf(PackedHandle{1, 2}), hashOf(PackedHandle{1, 2}));
    EXPECT_NE(hashOf(PackedHandle{1, 2}), hashOf(PackedHandle{2, 1}));
}

TEST(HashOf, IntegerFastPathDiffersFromByteHashing) {
    uint64 const value{0x0123456789ABCDEFull};
    EXPECT_NE(hashOf(value), hashBytes(&value, sizeof(value)));
}

//////////////////////////////////////////////////////
// Combining

TEST(HashCombine, IsDeterministic) {
    EXPECT_EQ(hashCombine(1, 2), hashCombine(1, 2));
}

TEST(HashCombine, IsOrderSensitive) {
    EXPECT_NE(hashCombine(1, 2), hashCombine(2, 1));
}

TEST(HashCombine, DiffersFromItsInputs) {
    hash_t const a{hashOf(1)};
    hash_t const b{hashOf(2)};
    hash_t const combined{hashCombine(a, b)};
    EXPECT_NE(combined, a);
    EXPECT_NE(combined, b);
}

//////////////////////////////////////////////////////
// Distribution

TEST(Hashing, ProducesDistinctValuesForSequentialKeys) {
    constexpr int keyCount{4096};

    std::set<hash_t> integerHashes;
    std::set<hash_t> stringHashes;
    for (int key{0}; key < keyCount; ++key) {
        integerHashes.insert(hashOf(key));
        stringHashes.insert(hashOf("asset_" + std::to_string(key)));
    }

    EXPECT_EQ(integerHashes.size(), static_cast<size_t>(keyCount));
    EXPECT_EQ(stringHashes.size(), static_cast<size_t>(keyCount));
}
