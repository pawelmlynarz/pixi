cmake_minimum_required(VERSION 4.3 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/engine/tools/cmake")

# Configure this project environment.
include(project_config.cmake)

# --------------------------------------------------
# Project Setup
# --------------------------------------------------
project(${PROJECT_NAME} C CXX)

# Check host & target platform.
include(platform/platform_check)

# --------------------------------------------------
# Environment Configuration
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP OFF)

include(build)
px_set_compiler_options()

# --------------------------------------------------
# Build Targets
# --------------------------------------------------

add_subdirectory(engine)

if(BUILD_SANDBOX)
	set(SANDBOX_TARGET_NAME sandbox)
    add_subdirectory("${SANDBOX_TARGET_NAME}")
endif()

if(BUILD_GAME)
    add_subdirectory("${GAME_TARGET_NAME}")
endif()
