# --------------------------------------------------
# Groups sources in IDE into folder hierarchy
# --------------------------------------------------
function(group_sources_for_target sources)
    set(last_dir "")
    set(files "")

    if(NOT sources)
        return()
    endif()

    list(FILTER sources EXCLUDE REGEX "^$")
    if(NOT sources)
        return()
    endif()

    foreach(file ${sources})
        if(NOT IS_ABSOLUTE "${file}")
            set(file "${CMAKE_CURRENT_SOURCE_DIR}/${file}")
        endif()

        file(RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" "${file}")
        get_filename_component(dir "${relative_file}" PATH)

        if(NOT "${dir}" STREQUAL "${last_dir}")
            if(files)
                source_group("${last_dir}" FILES ${files})
            endif()
            set(files "")
        endif()

        list(APPEND files "${file}")
        set(last_dir "${dir}")
    endforeach()

    if(files)
        source_group("${last_dir}" FILES ${files})
    endif()
endfunction()
