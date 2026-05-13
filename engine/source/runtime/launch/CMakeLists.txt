# --------------------------------------------------
# Module:           Launch
# Type:             Static  
# --------------------------------------------------

include(utils)

set(MODULE_NAME launch)
set(MODULE_TARGET_NAME px${MODULE_NAME})

#
# Library (static only)
add_library(${MODULE_TARGET_NAME} STATIC "")
add_library(px::engine::launch ALIAS ${MODULE_TARGET_NAME})

#
# Dependencies
target_link_libraries(${MODULE_TARGET_NAME} 
        PRIVATE
        px::engine::core
        px::engine::engine
)

if(PX_WITH_EDITOR)
    target_link_libraries(${MODULE_TARGET_NAME}
            PRIVATE
            px::engine::editor::core
            px::engine::editor::engine
    )
endif()

#
# Common Sources
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        public/*.cpp public/*.h public/*.inl
        private/*.cpp private/*.h private/*.inl
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

#
# Configuration
target_sources(${MODULE_TARGET_NAME} PRIVATE ${MODULE_SOURCES})
target_include_directories(${MODULE_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
list(APPEND MODULE_COMPILE_DEFINITIONS PX_BUILD_LAUNCH)
target_compile_definitions(${MODULE_TARGET_NAME} PRIVATE ${MODULE_COMPILE_DEFINITIONS})
target_compile_options(${MODULE_TARGET_NAME} PRIVATE ${GLOB_COMPILE_OPTIONS})

#
# IDE grouping
set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
group_sources_for_target(${MODULE_TARGET_NAME})
