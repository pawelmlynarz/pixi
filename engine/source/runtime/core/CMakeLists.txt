# --------------------------------------------------
# Module:           Core
# Default Type:     Dynamic
# --------------------------------------------------

include(utils)
include(build)

set(MODULE_NAME core)
if(NOT PX_BUILD_MONOLITHIC)
    set(MODULE_TARGET_NAME px${MODULE_NAME})
    
    #
    # Library
    if(PX_BUILD_SHARED)
        add_library(${MODULE_TARGET_NAME} SHARED "")
    else()
        add_library(${MODULE_TARGET_NAME} STATIC "")
    endif()
    add_library(px::core ALIAS ${MODULE_TARGET_NAME})
endif()

#
# Dependencies
target_link_libraries(${MODULE_TARGET_NAME}
        PRIVATE
        glfw
        PUBLIC
        glm
        spdlog
)

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.inl
)
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]public[/\\\\]platform[/\\\\]windows[/\\\\].*")
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]private[/\\\\]platform[/\\\\]windows[/\\\\].*")

#
# Platform Sources
if(WIN32)
    file(GLOB_RECURSE MODULE_PLATFORM_SOURCES CONFIGURE_DEPENDS
            public/platform/windows/*.cpp public/platform/windows/*.h public/platform/windows/*.inl
            private/platform/windows/*.cpp private/platform/windows/*.h private/platform/windows/*.inl
    )
endif()
list(APPEND MODULE_SOURCES ${MODULE_PLATFORM_SOURCES})

#
# Configuration
target_sources(${MODULE_TARGET_NAME} PRIVATE ${MODULE_SOURCES})
target_include_directories(${MODULE_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)
if(NOT BUILD_CLANG_TIDY)
target_precompile_headers(${MODULE_TARGET_NAME} PRIVATE
        ${MODULE_NAME}_pch.h
)
endif()

set_engine_module_properties(${MODULE_NAME})

#
# IDE grouping
if(NOT PX_BUILD_MONOLITHIC)
    set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
    group_sources_for_target(${MODULE_SOURCES})
endif()
