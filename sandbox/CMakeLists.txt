set(SANDBOX_TARGET_NAME sandbox)

set(SANDBOX_ROOT "${CMAKE_CURRENT_LIST_DIR}")

add_executable(${SANDBOX_TARGET_NAME})

add_subdirectory(source)

target_link_libraries(${SANDBOX_TARGET_NAME} PRIVATE
        pixi::engine
)

file(GLOB_RECURSE SANDBOX_CMAKE_FILES
        "${SANDBOX_ROOT}/CMakeLists.txt"
        "${SANDBOX_ROOT}/source/CMakeLists.txt"
)

target_sources(${SANDBOX_TARGET_NAME} PRIVATE
        ${SANDBOX_CMAKE_FILES}
)