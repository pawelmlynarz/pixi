// © 2026 Pawel Mlynarz

#pragma once

// NOLINTBEGIN
// clang-format off

//
// DLL Import/Export

#define DLLEXPORT __declspec(dllexport)
#define DLLIMPORT __declspec(dllimport)

//
// Preprocessor Utility

#define PX_PRIVATE_STRINGIZE(Token) #Token
#define PX_STRINGIZE(Token) PX_PRIVATE_STRINGIZE(Token)

#define PX_JOIN(TokenA, TokenB) PX_PRIVATE_JOIN(TokenA, TokenB)
#define PX_PRIVATE_JOIN(TokenA, TokenB) TokenA##TokenB

//
// Platform Headers Utility

#if PLATFORM_WINDOWS
#define COMPILED_PLATFORM_HEADER(HeaderFile) PX_STRINGIZE(windows/PX_JOIN(windows_, HeaderFile))
#else
#error Unsupported platform: compiled platform header format not provided.
#endif

// clang-format on
// NOLINTEND
