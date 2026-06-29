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
option(PX_BUILD_SHARED "Builds engine modules as dll(s)." ON)

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

# Library
if(PX_BUILD_SHARED)
    add_library(${ENGINE_TARGET_NAME} SHARED "")
else()
    add_library(${ENGINE_TARGET_NAME} STATIC "")
endif()
add_library(px::Engine ALIAS ${ENGINE_TARGET_NAME})

px_set_engine_target_properties(${ENGINE_TARGET_NAME})

#
# CMake Engine Sources
file(GLOB ENGINE_CMAKE_FILES
        "CMakeLists.txt"
        tools/cmake/*.cmake
)
file(GLOB_RECURSE ENGINE_CMAKE_FILES_RUNTIME
        source/runtime/CMakeLists.txt
)
list(APPEND ENGINE_CMAKE_FILES ${ENGINE_CMAKE_FILES_RUNTIME})
list(FILTER ENGINE_CMAKE_FILES EXCLUDE REGEX "[/\\\\]launch[/\\\\].*")
target_sources(${ENGINE_TARGET_NAME} PRIVATE ${ENGINE_CMAKE_FILES})

#
# Engine Editor Target
set(ENGINE_ED_MODULE_NAME EngineEditor)
set(ENGINE_ED_TARGET_NAME px${ENGINE_ED_MODULE_NAME})

# Library
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

# CMake Engine Editor Sources
file(GLOB_RECURSE ENGINE_ED_CMAKE_FILES_RUNTIME
        source/editor/CMakeLists.txt
)
target_sources(${ENGINE_ED_TARGET_NAME} PRIVATE ${ENGINE_ED_CMAKE_FILES_RUNTIME})


#
# Engine Launch Target

set(ENGINE_LAUNCH_MODULE_NAME EngineLaunch)
set(ENGINE_LAUNCH_TARGET_NAME px${ENGINE_LAUNCH_MODULE_NAME})

# Library (static only)
add_library(${ENGINE_LAUNCH_TARGET_NAME} STATIC "")
add_library(px::EngineLaunch ALIAS ${ENGINE_LAUNCH_TARGET_NAME})

# --------------------------------------------------
# Module(s) Subdirectories
# --------------------------------------------------

add_subdirectory(source)

group_sources_for_target(${ENGINE_TARGET_NAME})
group_sources_for_target(${ENGINE_ED_TARGET_NAME})
