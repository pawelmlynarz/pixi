# --------------------------------------------------
# Check if clang-format executable exists
# --------------------------------------------------
find_program(CLANG_FORMAT_EXE clang-format)
if (NOT CLANG_FORMAT_EXE)
    message(FATAL_ERROR "Unable to find clang-format executable.")
endif()

# --------------------------------------------------
# Prepare list of source files
# --------------------------------------------------
set(SOURCES "")
set(FORMAT_DIRECTORIES engine/source)
list(APPEND FORMAT_DIRECTORIES sandbox/source)

foreach (DIRECTORY IN LISTS FORMAT_DIRECTORIES)
    file(GLOB_RECURSE FILES
            "${DIRECTORY}/*.h"
            "${DIRECTORY}/*.hpp"
            "${DIRECTORY}/*.cpp"
            "${DIRECTORY}/*.inl"
    )
    list(APPEND SOURCES ${FILES})
endforeach()

list(FILTER SOURCES EXCLUDE REGEX "third_party")

# --------------------------------------------------
# Run clang-format
# --------------------------------------------------
execute_process(
    COMMAND ${CLANG_FORMAT_EXE} -i ${SOURCES}
    RESULT_VARIABLE EXIT_CODE
    OUTPUT_VARIABLE STDOUT
    ERROR_VARIABLE STDERR
)

if (NOT EXIT_CODE STREQUAL 0)
    message(FATAL_ERROR
        "clang-format process failed with exit code: ${EXIT_CODE}\n"
        "stdout:\n${STDOUT}\n"
        "stderr:\n${STDERR}"
    )
endif()
