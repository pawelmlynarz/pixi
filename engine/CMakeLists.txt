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

#
# Whether to build engine as separate dll per module or single dll.
option(PX_BUILD_MONOLITHIC "Engine monolithic dll build." ON)

# Force MONOLITHIC in static mode as it doesn't make any sense to build separate static libs.
if(NOT PX_BUILD_SHARED)
	set(PX_BUILD_MONOLITHIC ON CACHE BOOL "Engine monolithic dll build." FORCE)
endif()


if(PX_BUILD_MONOLITHIC)
    set(MONO_MODULE_NAME engine)
    set(MODULE_TARGET_NAME px${MONO_MODULE_NAME})
    
    if(PX_BUILD_SHARED)
        add_library(${MODULE_TARGET_NAME} SHARED "")
    else()
        add_library(${MODULE_TARGET_NAME} STATIC "")
    endif()

    add_library(px::mono::engine ALIAS ${MODULE_TARGET_NAME})
	
	file(GLOB_RECURSE ENGINE_CMAKE_FILES
        "CMakeLists.txt"
        tools/cmake/*.cmake
	)
	target_sources(${MODULE_TARGET_NAME} PRIVATE
        ${ENGINE_CMAKE_FILES}
	)
endif()

set(PX_ENGINE_COMPILE_DEFINITIONS)

if(PX_BUILD_SHARED)
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_SHARED)
else()
    list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PX_BUILD_STATIC)
endif()

if(TARGET_PLATFORM STREQUAL "Windows")
	list(APPEND PX_ENGINE_COMPILE_DEFINITIONS PLATFORM_WINDOWS)
endif()

# --------------------------------------------------
# Module(s) Subdirectories
# --------------------------------------------------

add_subdirectory(source)
