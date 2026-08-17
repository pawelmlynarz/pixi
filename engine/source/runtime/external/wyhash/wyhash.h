// © 2026 Pawel Mlynarz
// 
// This file contains code derived from the wyhash library (final version 3).
// https://github.com/wangyi-fudan/wyhash. The original work was released under The Unlicense.
//
// Local modifications:
//  - Replaced the original include guard with #pragma once.
//  - Wrapped every declaration in the px::detail namespace so that nothing leaks into the global
//    namespace. The standard library includes are deliberately kept outside of it.
//  - Undefined the internal macros at the end of the file so that they do not leak into translation
//    units that include this header.
//
// Do not include this header directly, use core's "common/hash.h" instead.

#pragma once

#ifndef WYHASH_CONDOM
// protections that produce different results:
// 1: normal valid behavior
// 2: extra protection against entropy loss (probability=2^-63), aka. "blind multiplication"
#define WYHASH_CONDOM 1
#endif

#ifndef WYHASH_32BIT_MUM
// 0: normal version, slow on 32 bit systems
// 1: faster on 32 bit systems but produces different results, incompatible with wy2u0k function
#define WYHASH_32BIT_MUM 0
#endif

// includes - these must stay outside of the namespace below
#include <stdint.h>
#include <string.h>
#if defined(_MSC_VER) && defined(_M_X64)
#include <intrin.h>
#pragma intrinsic(_umul128)
#else
#include <immintrin.h>
#endif

// likely and unlikely macros
#if defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
#define _likely_(x) __builtin_expect(x, 1)
#define _unlikely_(x) __builtin_expect(x, 0)
#else
#define _likely_(x) (x)
#define _unlikely_(x) (x)
#endif

// endian macros
#ifndef WYHASH_LITTLE_ENDIAN
#if defined(_WIN32) || defined(__LITTLE_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 1
#elif defined(__BIG_ENDIAN__) || (defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#define WYHASH_LITTLE_ENDIAN 0
#else
#warning could not determine endianness! Falling back to little endian.
#define WYHASH_LITTLE_ENDIAN 1
#endif
#endif

namespace px::detail {

// 128bit multiply function
static inline uint64_t _wyrot(uint64_t x) { return (x >> 32) | (x << 32); }
static inline void _wymum(uint64_t* A, uint64_t* B) {
#if (WYHASH_32BIT_MUM)
    uint64_t hh = (*A >> 32) * (*B >> 32), hl = (*A >> 32) * (uint32_t)*B, lh = (uint32_t)*A * (*B >> 32), ll = (uint64_t)(uint32_t)*A * (uint32_t)*B;
#if (WYHASH_CONDOM > 1)
    *A ^= _wyrot(hl) ^ hh;
    *B ^= _wyrot(lh) ^ ll;
#else
    *A = _wyrot(hl) ^ hh;
    *B = _wyrot(lh) ^ ll;
#endif
#elif defined(__SIZEOF_INT128__)
    __uint128_t r = *A;
    r *= *B;
#if (WYHASH_CONDOM > 1)
    *A ^= (uint64_t)r;
    *B ^= (uint64_t)(r >> 64);
#else
    *A = (uint64_t)r;
    *B = (uint64_t)(r >> 64);
#endif
#elif defined(_MSC_VER) && defined(_M_X64)
#if (WYHASH_CONDOM > 1)
    uint64_t a, b;
    a = _umul128(*A, *B, &b);
    *A ^= a;
    *B ^= b;
#else
    *A = _umul128(*A, *B, B);
#endif
#else
    uint64_t ha = *A >> 32, hb = *B >> 32, la = (uint32_t)*A, lb = (uint32_t)*B, hi, lo;
    uint64_t rh = ha * hb, rm0 = ha * lb, rm1 = hb * la, rl = la * lb, t = rl + (rm0 << 32), c = t < rl;
    lo = t + (rm1 << 32);
    c += lo < t;
    hi = rh + (rm0 >> 32) + (rm1 >> 32) + c;
#if (WYHASH_CONDOM > 1)
    *A ^= lo;
    *B ^= hi;
#else
    *A = lo;
    *B = hi;
#endif
#endif
}

// multiply and xor mix function, aka MUM
static inline uint64_t _wymix(uint64_t A, uint64_t B) {
    _wymum(&A, &B);
    return A ^ B;
}

// read functions
#if (WYHASH_LITTLE_ENDIAN)
static inline uint64_t _wyr8(uint8_t const* p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return v;
}
static inline uint64_t _wyr4(uint8_t const* p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return v;
}
#elif defined(__GNUC__) || defined(__INTEL_COMPILER) || defined(__clang__)
static inline uint64_t _wyr8(uint8_t const* p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return __builtin_bswap64(v);
}
static inline uint64_t _wyr4(uint8_t const* p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return __builtin_bswap32(v);
}
#elif defined(_MSC_VER)
static inline uint64_t _wyr8(uint8_t const* p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return _byteswap_uint64(v);
}
static inline uint64_t _wyr4(uint8_t const* p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return _byteswap_ulong(v);
}
#else
static inline uint64_t _wyr8(uint8_t const* p) {
    uint64_t v;
    memcpy(&v, p, 8);
    return (((v >> 56) & 0xff) | ((v >> 40) & 0xff00) | ((v >> 24) & 0xff0000) | ((v >> 8) & 0xff000000) | ((v << 8) & 0xff00000000) | ((v << 24) & 0xff0000000000) | ((v << 40) & 0xff000000000000) | ((v << 56) & 0xff00000000000000));
}
static inline uint64_t _wyr4(uint8_t const* p) {
    uint32_t v;
    memcpy(&v, p, 4);
    return (((v >> 24) & 0xff) | ((v >> 8) & 0xff00) | ((v << 8) & 0xff0000) | ((v << 24) & 0xff000000));
}
#endif
static inline uint64_t _wyr3(uint8_t const* p, size_t k) { return (((uint64_t)p[0]) << 16) | (((uint64_t)p[k >> 1]) << 8) | p[k - 1]; }

// wyhash main function
static inline uint64_t wyhash(void const* key, size_t len, uint64_t seed, uint64_t const* secret) {
    uint8_t const* p = (uint8_t const*)key;
    seed ^= *secret;
    uint64_t a, b;
    if (_likely_(len <= 16)) {
        if (_likely_(len >= 4)) {
            a = (_wyr4(p) << 32) | _wyr4(p + ((len >> 3) << 2));
            b = (_wyr4(p + len - 4) << 32) | _wyr4(p + len - 4 - ((len >> 3) << 2));
        } else if (_likely_(len > 0)) {
            a = _wyr3(p, len);
            b = 0;
        } else
            a = b = 0;
    } else {
        size_t i = len;
        if (_unlikely_(i > 48)) {
            uint64_t see1 = seed, see2 = seed;
            do {
                seed = _wymix(_wyr8(p) ^ secret[1], _wyr8(p + 8) ^ seed);
                see1 = _wymix(_wyr8(p + 16) ^ secret[2], _wyr8(p + 24) ^ see1);
                see2 = _wymix(_wyr8(p + 32) ^ secret[3], _wyr8(p + 40) ^ see2);
                p += 48;
                i -= 48;
            } while (_likely_(i > 48));
            seed ^= see1 ^ see2;
        }
        while (_unlikely_(i > 16)) {
            seed = _wymix(_wyr8(p) ^ secret[1], _wyr8(p + 8) ^ seed);
            i -= 16;
            p += 16;
        }
        a = _wyr8(p + i - 16);
        b = _wyr8(p + i - 8);
    }
    return _wymix(secret[1] ^ len, _wymix(a ^ secret[1], b ^ seed));
}

// the default secret parameters
static uint64_t const _wyp[4] = {0xa0761d6478bd642full, 0xe7037ed1a0b428dbull, 0x8ebc6af09c88c6e3ull, 0x589965cc75374cc3ull};

// a useful 64bit-64bit mix function to produce deterministic pseudo random numbers that can pass BigCrush and PractRand
static inline uint64_t wyhash64(uint64_t A, uint64_t B) {
    A ^= 0xa0761d6478bd642full;
    B ^= 0xe7037ed1a0b428dbull;
    _wymum(&A, &B);
    return _wymix(A ^ 0xa0761d6478bd642full, B ^ 0xe7037ed1a0b428dbull);
}

// The wyrand PRNG that pass BigCrush and PractRand
static inline uint64_t wyrand(uint64_t* seed) {
    *seed += 0xa0761d6478bd642full;
    return _wymix(*seed, *seed ^ 0xe7037ed1a0b428dbull);
}

// convert any 64 bit pseudo random numbers to uniform distribution [0,1). It can be combined with wyrand, wyhash64 or wyhash.
static inline double wy2u01(uint64_t r) {
    double const _wynorm = 1.0 / (1ull << 52);
    return (r >> 12) * _wynorm;
}

#if (!WYHASH_32BIT_MUM)
// fast range integer random number generation on [0,k) credit to Daniel Lemire. May not work when WYHASH_32BIT_MUM=1. It can be combined with wyrand, wyhash64 or wyhash.
static inline uint64_t wy2u0k(uint64_t r, uint64_t k) {
    _wymum(&r, &k);
    return k;
}
#endif

} // namespace px::detail

// The internal macros are undefined so that they do not leak into including translation units.
#undef _likely_
#undef _unlikely_
#undef WYHASH_LITTLE_ENDIAN
#undef WYHASH_CONDOM
#undef WYHASH_32BIT_MUM
