cmake_minimum_required(VERSION 4.3 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/engine/tools/cmake")

# --------------------------------------------------
# Setup project name
# --------------------------------------------------
set(PROJECT_NAME pixi)

if(DEFINED PROJECT_NAME_OVERRIDE)
    set(PROJECT_NAME "${PROJECT_NAME_OVERRIDE}")
endif()

project(${PROJECT_NAME} C CXX)

# --------------------------------------------------
# Configuration
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------------------------------------
# Build targets
# --------------------------------------------------

add_subdirectory(engine)

option(PIXI_BUILD_SANDBOX "Build sandbox executable" ON)
if(PIXI_BUILD_SANDBOX)
    add_subdirectory(sandbox)
endif()
