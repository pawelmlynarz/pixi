# --------------------------------------------------
# Component:        Launch (Always Static)
# --------------------------------------------------

include(utils)
include(build)

set(COMPONENT_NAME launch)
set(LAUNCH_TARGET_NAME pxLaunch)

#
# Library (static only)
add_library(${LAUNCH_TARGET_NAME} STATIC "")
add_library(px::launch ALIAS ${LAUNCH_TARGET_NAME})

#
# Dependencies
target_link_libraries(${LAUNCH_TARGET_NAME} 
        PRIVATE
        px::Engine
        $<$<CONFIG:DebugEditor>:px::EngineEditor>
)

#
# Common Sources
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.inl
)
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]public[/\\\\]platform[/\\\\].*")
list(FILTER MODULE_SOURCES EXCLUDE REGEX "[/\\\\]private[/\\\\]platform[/\\\\].*")

#
# Platform Sources
if(WIN32)
    file(GLOB_RECURSE MODULE_PLATFORM_SOURCES CONFIGURE_DEPENDS
            public/windows/*.cpp public/windows/*.h public/windows/*.inl
            private/windows/*.cpp private/windows/*.h private/windows/*.inl
    )
endif()
list(APPEND MODULE_SOURCES ${MODULE_PLATFORM_SOURCES})

target_sources(${LAUNCH_TARGET_NAME} PRIVATE ${MODULE_SOURCES})

target_include_directories(${LAUNCH_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

if(NOT BUILD_CLANG_TIDY)
target_precompile_headers(${LAUNCH_TARGET_NAME} PRIVATE
        ${COMPONENT_NAME}_pch.h
)
endif()

px_set_engine_launch_target_properties(${LAUNCH_TARGET_NAME})

#
# IDE grouping
# set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
# group_sources_for_target(${MODULE_SOURCES})
