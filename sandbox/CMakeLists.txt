set(SANDBOX_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Sandbox Target
# --------------------------------------------------

add_executable(${SANDBOX_TARGET_NAME})

if(WIN32)
    set_target_properties(${SANDBOX_TARGET_NAME}
            PROPERTIES
            WIN32_EXECUTABLE ${WIN32}
    )
endif()

add_subdirectory(source)

target_link_libraries(${SANDBOX_TARGET_NAME} PRIVATE
        px::engine::launch
)

#
# Common Sources
file(GLOB_RECURSE SANDBOX_CMAKE_FILES
        "${SANDBOX_ROOT}/CMakeLists.txt"
        "${SANDBOX_ROOT}/source/CMakeLists.txt"
)

target_sources(${SANDBOX_TARGET_NAME} PRIVATE
        ${SANDBOX_CMAKE_FILES}
)

#
# Configuration
target_compile_options(${SANDBOX_TARGET_NAME} PRIVATE ${GLOB_COMPILE_OPTIONS})

# --------------------------------------------------
# Post Build
# --------------------------------------------------

if(PX_BUILD_SHARED)
    add_custom_command(TARGET ${SANDBOX_TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:${SANDBOX_TARGET_NAME}>
            $<TARGET_FILE_DIR:${SANDBOX_TARGET_NAME}>
            COMMENT "Copying engine dlls into sandbox executable directory."
            COMMAND_EXPAND_LISTS
    )
endif()
