# --------------------------------------------------
# Third party library fetch
# --------------------------------------------------

include(FetchContent)
set(FETCHCONTENT_BASE_DIR "${CMAKE_BINARY_DIR}/third_party/" CACHE PATH "" FORCE)

# third_party/nri

option(NRI_STATIC_LIBRARY "" OFF)
option(NRI_ENABLE_VK_SUPPORT "" ON)
option(NRI_ENABLE_VK_SUPPORT "" ON)
option(NRI_ENABLE_NONE_SUPPORT "" OFF)
option(NRI_ENABLE_D3D11_SUPPORT "" OFF)
option(NRI_ENABLE_D3D12_SUPPORT "" OFF)
option(NRI_ENABLE_NVTX_SUPPORT "" OFF)
option(NRI_ENABLE_IMGUI_EXTENSION "" ON)

fetchcontent_declare(
        nri
        DOWNLOAD_EXTRACT_TIMESTAMP 1
        DOWNLOAD_NO_PROGRESS 1
        URL https://github.com/NVIDIA-RTX/NRI/archive/refs/tags/v179.zip
)
list(APPEND DEPS nri)

# third_party/MathLib

fetchcontent_declare(
        mathlib
        DOWNLOAD_EXTRACT_TIMESTAMP 1
        DOWNLOAD_NO_PROGRESS 1
        URL https://github.com/NVIDIA-RTX/MathLib/archive/refs/tags/v11.zip
)
list(APPEND DEPS mathlib)

# third_party/imgui

fetchcontent_declare(
        imgui
        DOWNLOAD_EXTRACT_TIMESTAMP 1
        DOWNLOAD_NO_PROGRESS 1
        SOURCE_SUBDIR "ignore CMakeLists.txt"
        URL https://github.com/ocornut/imgui/archive/refs/tags/v1.92.6.zip
)
list(APPEND DEPS imgui)

# third_party/GLFW

option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)

fetchcontent_declare(
        glfw
        DOWNLOAD_EXTRACT_TIMESTAMP 1
        DOWNLOAD_NO_PROGRESS 1
        URL https://github.com/glfw/glfw/archive/fdd14e65b1c29e4e6df875fb5669ec00d6793531.zip
)
list(APPEND DEPS glfw)

# third_party/ShaderMake

if(NOT TARGET ShaderMake)
    # could be already added by NRI
    option(SHADERMAKE_TOOL "" ON)

    fetchcontent_declare(
            shadermake
            DOWNLOAD_EXTRACT_TIMESTAMP 1
            DOWNLOAD_NO_PROGRESS 1
            URL https://github.com/NVIDIA-RTX/ShaderMake/archive/18f5a344e7ca8fa65daaf079d07bc8ce38453e05.zip
    )
    list(APPEND DEPS shadermake)
endif()

if(DEPS)
    message("PixiEngine: downloading dependencies:")
    message(STATUS "${DEPS} ...")
    fetchcontent_makeavailable(${DEPS})
endif()

# --------------------------------------------------
# IDE Targets Structure
# --------------------------------------------------

function(set_third_party_filter target additional_filter)
    if(TARGET ${target})
        set_target_properties(${target} PROPERTIES FOLDER "engine/third_party/${additional_filter}")
    else()
        message(NOTICE "Target ${target} not specified.")    
    endif()
endfunction()

set_third_party_filter(ShaderMake "ShaderMake")
set_third_party_filter(ShaderMakeBlob "ShaderMake")
set_third_party_filter(ShaderMake-build "ShaderMake")
set_third_party_filter(glfw "GLFW3")
set_third_party_filter(update_mappings "GLFW3")
set_third_party_filter(MathLib "")
set_third_party_filter(NRI "NRI")
set_third_party_filter(NRI_Shared "NRI")
set_third_party_filter(NRI_Validation "NRI")
set_third_party_filter(NRI_VK "NRI")

# --------------------------------------------------
# Manual Third Party Building (ignored CMakeLists)
# --------------------------------------------------

file(GLOB IMGUI_SOURCES "${imgui_SOURCE_DIR}/*.cpp" "${imgui_SOURCE_DIR}/*.h")
source_group("" FILES ${IMGUI_SOURCES})
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC "${imgui_SOURCE_DIR}")
set_third_party_filter(imgui "")
