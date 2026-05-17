# --------------------------------------------------
# Module:           Engine
# Default Type:     Dynamic
# --------------------------------------------------

include(utils)

set(MODULE_NAME engine)
set(MODULE_TARGET_NAME px${MODULE_NAME})

#
# Library
if(PX_BUILD_SHARED)
    add_library(${MODULE_TARGET_NAME} SHARED "")
else()
    add_library(${MODULE_TARGET_NAME} STATIC "")
endif()
add_library(px::engine::engine ALIAS ${MODULE_TARGET_NAME})

#
# Dependencies
target_link_libraries(${MODULE_TARGET_NAME}
        PRIVATE
        px::engine::core
)

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        public/*.cpp public/*.h public/*.inl
        private/*.cpp private/*.h private/*.inl
)

#
# Configuration
target_sources(${MODULE_TARGET_NAME} PRIVATE ${MODULE_SOURCES})
target_include_directories(${MODULE_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
list(APPEND MODULE_COMPILE_DEFINITIONS PX_BUILD_ENGINE)
target_compile_definitions(${MODULE_TARGET_NAME} PRIVATE ${MODULE_COMPILE_DEFINITIONS})
target_compile_options(${MODULE_TARGET_NAME} PRIVATE ${GLOB_COMPILE_OPTIONS})

#
# IDE grouping
set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
group_sources_for_target(${MODULE_TARGET_NAME})
