cmake_minimum_required(VERSION 4.3 FATAL_ERROR)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/engine/tools/cmake")

include(project_config.cmake)

# --------------------------------------------------
# Setup project
# --------------------------------------------------
project(${PROJECT_NAME} C CXX)

# --------------------------------------------------
# Environment configuration
# --------------------------------------------------

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
set(CMAKE_EXPERIMENTAL_CXX_MODULE_DYNDEP OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(COMPILE_OPTIONS -mssse3 -Wextra)
elseif(MSVC)
    set(COMPILE_OPTIONS /W4 /WX
            /wd4324
    )
else()
    message(WARNING "Unknown compiler!")
endif()

# --------------------------------------------------
# Build targets
# --------------------------------------------------

add_subdirectory(engine)

if(BUILD_SANDBOX)
    add_subdirectory("${SANDBOX_TARGET_NAME}")
endif()

if(BUILD_GAME)
    add_subdirectory("${GAME_TARGET_NAME}")
endif()
