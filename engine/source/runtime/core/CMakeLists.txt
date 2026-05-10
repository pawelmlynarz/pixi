# --------------------------------------------------
# Module:           Core
# Default Type:     Dynamic
# --------------------------------------------------

include(utils)

set(MODULE_NAME core)
set(MODULE_TARGET_NAME px${MODULE_NAME})

#
# Library
if(PX_BUILD_SHARED)
    add_library(${MODULE_TARGET_NAME} SHARED "")
else()
    add_library(${MODULE_TARGET_NAME} STATIC "")
endif()
add_library(px::engine::core ALIAS ${MODULE_TARGET_NAME})

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        public/*.cpp public/*.h public/*.inl
        private/*.cpp private/*.h private/*.inl
)
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]public[/\\\\][^/\\\\]+[/\\\\][^/\\\\]+[/\\\\].*")
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]private[/\\\\][^/\\\\]+[/\\\\][^/\\\\]+[/\\\\].*")
#
# Platform Sources
if(WIN32)
    file(GLOB_RECURSE MODULE_PLATFORM_SOURCES CONFIGURE_DEPENDS
            public/common/windows/*.cpp public/common/windows/*.h public/common/windows/*.inl
            private/common/windows/*.cpp private/common/windows/*.h private/common/windows/*.inl
            public/window/windows/*.cpp public/window/windows/*.h public/window/windows/*.inl
            private/window/windows/*.cpp private/window/windows/*.h private/window/windows/*.inl
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

set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
list(APPEND MODULE_COMPILE_DEFINITIONS PX_BUILD_CORE)
target_compile_definitions(${MODULE_TARGET_NAME} PRIVATE ${MODULE_COMPILE_DEFINITIONS})
target_compile_options(${MODULE_TARGET_NAME} PRIVATE ${GLOB_COMPILE_OPTIONS})

#
# IDE grouping
set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
group_sources_for_target(${MODULE_TARGET_NAME})
