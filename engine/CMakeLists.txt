set(ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Engine Third Party Fetch
# --------------------------------------------------

include(fetch_third_party)

# --------------------------------------------------
# Engine Target(s) Configuration
# --------------------------------------------------

#
# Builds engine modules as dynamic libraries .
# An exception is Launch module which is obligatory to be static.
option(PX_BUILD_SHARED "Builds engine modules as separate dlls." ON)

option(PX_BUILD_MONOLITHIC "Mono" ON)

if(PX_BUILD_MONOLITHIC)
    set(MONO_MODULE_NAME engine)
    set(MODULE_TARGET_NAME px${MONO_MODULE_NAME})
    
    if(PX_BUILD_SHARED)
        add_library(${MODULE_TARGET_NAME} SHARED "")
    else()
        add_library(${MODULE_TARGET_NAME} STATIC "")
    endif()

    add_library(px::mono::engine ALIAS ${MODULE_TARGET_NAME})
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
