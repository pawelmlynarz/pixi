# --------------------------------------------------
# Module:           Frontend
# Default Type:     Dynamic
# --------------------------------------------------

include(utils)
include(build)

set(MODULE_NAME frontend)
if(NOT PX_BUILD_MONOLITHIC)
    set(MODULE_TARGET_NAME px${MODULE_NAME})
    
    #
    # Library
    if(PX_BUILD_SHARED)
        add_library(${MODULE_TARGET_NAME} SHARED "")
    else()
        add_library(${MODULE_TARGET_NAME} STATIC "")
    endif()
    add_library(px::frontend ALIAS ${MODULE_TARGET_NAME})
endif()

#
# Dependencies
if(NOT PX_BUILD_MONOLITHIC)
    target_link_libraries(${MODULE_TARGET_NAME}
            PUBLIC
            px::core
            px::rhi
            px::rendercore
    )
endif()

target_link_libraries(${MODULE_TARGET_NAME}
        PUBLIC
        imgui
)

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.inl
)

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
