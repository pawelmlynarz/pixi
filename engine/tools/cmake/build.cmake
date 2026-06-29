# Defines compiler options and optimization levels for all configurations.
function(px_set_compiler_options)
    if(MSVC)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /wd4324 /wd4100" CACHE STRING "" FORCE)
        
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Od /Ob0 /Zi /RTC1" CACHE STRING "" FORCE)
        set(CMAKE_CXX_FLAGS_DEBUGEDITOR "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "" FORCE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /O2 /Ob2 /Oi /Ot /Gy" CACHE STRING "" FORCE)

        set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} /DEBUG" CACHE STRING "" FORCE)
        set(CMAKE_EXE_LINKER_FLAGS_DEBUGEDITOR "${CMAKE_EXE_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF" CACHE STRING "" FORCE)

        set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /DEBUG" CACHE STRING "" FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_DEBUGEDITOR "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}" CACHE STRING "" FORCE)
        set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /OPT:REF /OPT:ICF" CACHE STRING "" FORCE)
    elseif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mssse3 -Wextra" CACHE STRING "" FORCE)
        
        set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g" CACHE STRING "" FORCE)
        set(CMAKE_CXX_FLAGS_DEBUGEDITOR "${CMAKE_CXX_FLAGS_DEBUGEDITOR}" CACHE STRING "" FORCE)
        set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3" CACHE STRING "" FORCE)
    else()
        message(FATAL_ERROR "Unknown compiler!")
    endif()
endfunction()

# Sets compilation properties for any target.
function(px_set_target_properties target_name)
    if(NOT TARGET ${target_name})
        message(FATAL_ERROR "set_target_properties: Target '${target_name}' does not exist.")
    endif()

    # Compile definitions.
    target_compile_definitions(${target_name}
            PUBLIC
            WITH_EDITOR=$<IF:$<CONFIG:DebugEditor>,1,0>
            WITH_IMGUI=$<IF:$<CONFIG:DebugEditor>,1,0>
    )

    # Common compile options.
    target_compile_options(${target_name} PRIVATE ${GLOB_COMPILE_OPTIONS})
endfunction()

function(_px_set_engine_target_properties_impl target_name)
    px_set_target_properties(${target_name})
    
    target_compile_definitions(${target_name}
            PRIVATE
            ${MODULE_COMPILE_DEFINITIONS}
    )
endfunction()

# Sets compilation properties for an engine target.
function(px_set_engine_target_properties target_name)
    set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
    
    list(APPEND MODULE_COMPILE_DEFINITIONS "PX_BUILD_ENGINE")

    _px_set_engine_target_properties_impl(${target_name})
endfunction()

# Sets compilation properties for an engine editor target.
function(px_set_engine_editor_target_properties target_name)
    set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
    
    list(APPEND MODULE_COMPILE_DEFINITIONS "PX_BUILD_ENGINE_EDITOR")

    _px_set_engine_target_properties_impl(${target_name})
endfunction()

# Sets compilation properties for an static engine launch target.
function(px_set_engine_launch_target_properties target_name)
    set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
    
    _px_set_engine_target_properties_impl(${target_name})
endfunction()


# Excludes module from default compilation in all configurations except one.
# A module can be build anyway if hard link exists - refer generator expressions. 
function(px_exclude_module_from_default_build_except module enabled_config)
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${config}" config_upper)

        if("${config}" STREQUAL "${enabled_config}")
            set(exclude FALSE)
        else()
            set(exclude TRUE)
        endif()

        set_target_properties(${module} PROPERTIES
                EXCLUDE_FROM_DEFAULT_BUILD_${config_upper} ${exclude}
        )
    endforeach()
endfunction()
