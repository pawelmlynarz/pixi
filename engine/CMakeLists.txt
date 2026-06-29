set(ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Engine Third Party Fetch
# --------------------------------------------------

include(fetch_third_party)

# --------------------------------------------------
# Engine Target(s) Configuration
# --------------------------------------------------

#
# Builds engine module(s) as dynamic libraries.
# An exception is Launch module which is obligatory to be static.
option(PX_BUILD_SHARED "Builds engine modules as dll(s)." OFF)

# --------------------------------------------------
# Global Compile Definitions
# --------------------------------------------------

set(PX_ENGINE_COMPILE_DEFINITIONS)

if (PX_BUILD_SHARED)
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_SHARED)
else ()
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_STATIC)
endif ()

if (TARGET_PLATFORM STREQUAL "Windows")
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PLATFORM_WINDOWS)
endif ()

#
# Engine Target
set(ENGINE_MODULE_NAME Engine)
set(ENGINE_TARGET_NAME px${ENGINE_MODULE_NAME})

if(PX_BUILD_SHARED)
    add_library(${ENGINE_TARGET_NAME} SHARED "")
else()
    add_library(${ENGINE_TARGET_NAME} STATIC "")
endif()
add_library(px::Engine ALIAS ${ENGINE_TARGET_NAME})

px_set_engine_target_properties(${ENGINE_TARGET_NAME})

#
# CMake Sources for IDE
file(GLOB_RECURSE ENGINE_CMAKE_FILES
        "CMakeLists.txt"
        tools/cmake/*.cmake
)
target_sources(${ENGINE_TARGET_NAME} PRIVATE ${ENGINE_CMAKE_FILES})

#
# Engine Editor Target
set(ENGINE_ED_MODULE_NAME EngineEditor)
set(ENGINE_ED_TARGET_NAME px${ENGINE_ED_MODULE_NAME})

if(PX_BUILD_SHARED)
    add_library(${ENGINE_ED_TARGET_NAME} SHARED "")
else()
    add_library(${ENGINE_ED_TARGET_NAME} STATIC "")
endif()
add_library(px::EngineEditor ALIAS ${ENGINE_ED_TARGET_NAME})

target_link_libraries(${ENGINE_ED_TARGET_NAME}
        PRIVATE
        px::Engine
)

px_set_engine_editor_target_properties(${ENGINE_ED_TARGET_NAME})

px_exclude_module_from_default_build_except(${ENGINE_ED_TARGET_NAME} DebugEditor)

# --------------------------------------------------
# Module(s) Subdirectories
# --------------------------------------------------

add_subdirectory(source)
