set(TESTS_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Tests Target
# --------------------------------------------------

add_executable(${TESTS_TARGET_NAME})

add_subdirectory(source)

target_link_libraries(${TESTS_TARGET_NAME} PRIVATE
        px::Engine
        GTest::gtest_main
)

target_compile_definitions(${TESTS_TARGET_NAME} PRIVATE
        ${PX_ENGINE_COMPILE_DEFINITIONS}
)

#
# Common Sources
file(GLOB_RECURSE TESTS_CMAKE_FILES
        "${TESTS_ROOT}/CMakeLists.txt"
        "${TESTS_ROOT}/source/CMakeLists.txt"
)

target_sources(${TESTS_TARGET_NAME} PRIVATE
        ${TESTS_CMAKE_FILES}
)

#
# Configuration
px_set_target_properties(${TESTS_TARGET_NAME})

set_target_properties(${TESTS_TARGET_NAME} PROPERTIES FOLDER "tests")

group_sources_for_target(${TESTS_TARGET_NAME})

# --------------------------------------------------
# Test Registration
# --------------------------------------------------

include(GoogleTest)

gtest_discover_tests(${TESTS_TARGET_NAME}
        DISCOVERY_MODE PRE_TEST
)

# --------------------------------------------------
# Post Build
# --------------------------------------------------

add_custom_command(TARGET ${TESTS_TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_RUNTIME_DLLS:${TESTS_TARGET_NAME}>
        $<TARGET_FILE_DIR:${TESTS_TARGET_NAME}>
        COMMENT "Copying engine dlls into tests executable directory."
        COMMAND_EXPAND_LISTS
)
