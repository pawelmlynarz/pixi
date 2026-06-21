# --------------------------------------------------
# Module:           Launch
# Type:             Static  
# --------------------------------------------------

include(utils)
include(build)

set(MODULE_NAME launch)
set(MODULE_TARGET_NAME px${MODULE_NAME})

#
# Library (static only)
add_library(${MODULE_TARGET_NAME} STATIC "")
add_library(px::launch ALIAS ${MODULE_TARGET_NAME})

#
# Dependencies
if(NOT PX_BUILD_MONOLITHIC)
    target_link_libraries(${MODULE_TARGET_NAME} 
            PRIVATE
            px::core
            px::engine
            px::rhi
            px::frontend
    )
    
    target_link_libraries(${MODULE_TARGET_NAME}
            PRIVATE
            $<$<CONFIG:DebugEditor>:px::editor::core>
            $<$<CONFIG:DebugEditor>:px::editor::engine>
    )
else()
    target_link_libraries(${MODULE_TARGET_NAME} PRIVATE px::mono::engine)
endif()

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
