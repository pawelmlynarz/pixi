# --------------------------------------------------
# Component:        Core
# --------------------------------------------------

include(utils)
include(build)

set(COMPONENT_NAME core)

#
# Dependencies
target_link_libraries(${ENGINE_TARGET_NAME}
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

target_sources(${ENGINE_TARGET_NAME} PRIVATE ${MODULE_SOURCES})

target_include_directories(${ENGINE_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

if(NOT BUILD_CLANG_TIDY)
    target_precompile_headers(${ENGINE_TARGET_NAME} PRIVATE
            ${COMPONENT_NAME}_pch.h
    )
endif()
