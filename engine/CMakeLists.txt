set(ENGINE_TARGET_NAME engine)

set(ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}")

add_library(${ENGINE_TARGET_NAME} STATIC "")
add_library(pixi::engine ALIAS ${ENGINE_TARGET_NAME})

add_subdirectory(source)

file(GLOB_RECURSE ENGINE_CMAKE_FILES
        "${ENGINE_ROOT}/CMakeLists.txt"
        "${ENGINE_ROOT}/tools/cmake/*.cmake"
        "${ENGINE_ROOT}/source/CMakeLists.txt"
)

target_sources(${ENGINE_TARGET_NAME} PRIVATE
        ${ENGINE_CMAKE_FILES}
)