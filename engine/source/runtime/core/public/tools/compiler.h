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
#   define COMPILED_PLATFORM_HEADER(HeaderFile) PX_STRINGIZE(platform/windows/PX_JOIN(windows_, HeaderFile))
#else
#   error Unsupported platform: compiled platform header format not provided.
#endif

//
// Shared build API defs.

#ifdef PX_BUILD_SHARED
#   ifdef PX_BUILD_ENGINE
#       define PXENGINE_API DLLEXPORT
#   else
#       define PXENGINE_API DLLIMPORT
#   endif

#   ifdef PX_BUILD_ENGINE_EDITOR
#       define PXENGINE_EDITOR_API DLLEXPORT
#   else
#       define PXENGINE_EDITOR_API DLLIMPORT
#   endif
#else
#   define PXENGINE_API
#endif

// clang-format on
// NOLINTEND
