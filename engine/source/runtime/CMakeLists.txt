add_subdirectory(external)
add_subdirectory(core)
add_subdirectory(launch)
add_subdirectory(engine)
add_subdirectory(rhi)
add_subdirectory(rendercore)
add_subdirectory(frontend)

target_include_directories(${ENGINE_TARGET_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)
