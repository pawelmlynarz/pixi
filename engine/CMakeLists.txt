set(ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Engine Third Party Fetch
# --------------------------------------------------

if(NOT BUILD_CLANG_TIDY)
    include(fetch_third_party)
endif()

# --------------------------------------------------
# Engine Target(s) Configuration
# --------------------------------------------------

#
# Builds engine modules as dynamic libraries .
# An exception is Launch module which is obligatory to be static.
option(PX_BUILD_SHARED "Builds engine modules as separate dlls." ON)

#
# Builds engine with editor
option(PX_WITH_EDITOR "Builds engine with development editor." ON)

set(PX_ENGINE_COMPILE_DEFINITIONS)

if(PX_BUILD_SHARED)
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_SHARED)
else()
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_STATIC)
endif()

if(PX_WITH_EDITOR)
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS WITH_EDITOR)   
endif()

if(PLATFORM_WINDOWS)
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PLATFORM_WINDOWS)
endif()

# --------------------------------------------------
# Module(s) Subdirectories
# --------------------------------------------------

add_subdirectory(source)
