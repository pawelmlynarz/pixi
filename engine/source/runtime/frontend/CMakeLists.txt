# --------------------------------------------------
# Component:        Frontend
# --------------------------------------------------

include(utils)
include(build)

set(COMPONENT_NAME frontend)

#
# Dependencies
target_link_libraries(${ENGINE_TARGET_NAME}
        PUBLIC
        $<$<CONFIG:DebugEditor>:imgui>
)

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.inl
)
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

#
# IDE grouping
# set_target_properties(${MODULE_TARGET_NAME} PROPERTIES FOLDER "engine/runtime/")
# group_sources_for_target(${MODULE_SOURCES})
