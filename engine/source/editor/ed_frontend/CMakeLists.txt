# --------------------------------------------------
# Component:        EditorFrontend
# --------------------------------------------------

include(build)
include(utils)

set(COMPONENT_NAME editor_frontend)

#
# Dependencies
target_link_libraries(${ENGINE_ED_TARGET_NAME}
        PUBLIC
        imgui
)

#
# Common Sources                                         
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.cpp *.h *.inl
)
target_sources(${ENGINE_ED_TARGET_NAME} PRIVATE ${MODULE_SOURCES})

target_include_directories(${ENGINE_ED_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/public
)

if(NOT BUILD_CLANG_TIDY)
    target_precompile_headers(${ENGINE_ED_TARGET_NAME} PRIVATE
            ${COMPONENT_NAME}_pch.h
    )
endif()
