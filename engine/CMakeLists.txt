set(ENGINE_TARGET_NAME PixiEngine)

set(ENGINE_ROOT "${CMAKE_CURRENT_LIST_DIR}")

# --------------------------------------------------
# Engine Third Party
# --------------------------------------------------

include(fetch_third_party)

# --------------------------------------------------
# Engine Target Configuration
# --------------------------------------------------

add_library(${ENGINE_TARGET_NAME} STATIC "")
add_library(px::engine ALIAS ${ENGINE_TARGET_NAME})

add_subdirectory(source)

file(GLOB_RECURSE ENGINE_CMAKE_FILES
        "${ENGINE_ROOT}/CMakeLists.txt"
        "${ENGINE_ROOT}/tools/cmake/*.cmake"
        "${ENGINE_ROOT}/source/CMakeLists.txt"
)

target_sources(${ENGINE_TARGET_NAME} PRIVATE
        ${ENGINE_CMAKE_FILES}
)

target_link_libraries(${ENGINE_TARGET_NAME}
        PRIVATE
        glfw
        NRI
        imgui
        MathLib
)

target_include_directories(${ENGINE_TARGET_NAME}
        PRIVATE
        "${glfw_SOURCE_DIR}/include"
)

target_compile_options(${ENGINE_TARGET_NAME} PRIVATE ${COMPILE_OPTIONS})
set_target_properties(${ENGINE_TARGET_NAME} PROPERTIES FOLDER "engine")

# AgilitySDK requires specific symbols to be exported from the executable, which are not needed elsewhere.
# Any other method doesn't work. "PUBLIC" to make settings visible in the exe module.
if(MSVC AND NRI_ENABLE_AGILITY_SDK_SUPPORT)
    include(CheckLinkerFlag)
    check_linker_flag(CXX /NOEXP HAS_NOEXP)

    set(LINK_OPTIONS /NOIMPLIB)
    if(HAS_NOEXP)
        set(LINK_OPTIONS ${LINK_OPTIONS} /NOEXP)
    endif()

    target_link_options(${ENGINE_TARGET_NAME} PUBLIC ${LINK_OPTIONS})
endif()
