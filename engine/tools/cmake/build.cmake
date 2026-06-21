# Defines compiler options and optimization levels for all configurations.
function(set_compiler_options)
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

# Sets compilation properties for any module.
function(set_module_properties module_name)
    if(NOT TARGET ${module_name})
        message(FATAL_ERROR "set_module_properties: Module '${module_name}' does not exist.")
    endif()

    # Compile definitions.
    target_compile_definitions(${module_name}
            PUBLIC
            WITH_EDITOR=$<IF:$<CONFIG:DebugEditor>,1,0>
            WITH_IMGUI=$<NOT:$<CONFIG:Release>>
    )

    # Common compile options.
    target_compile_options(${module_name} PRIVATE ${GLOB_COMPILE_OPTIONS})
endfunction()

# Sets compilation properties for an engine module.
function(set_engine_module_properties module_name)
    string(TOUPPER "${module_name}" MODULE_NAME_UPPER)
    
    if (PX_BUILD_MONOLITHIC)
	    set_module_properties("px${MONO_MODULE_NAME}")
    else()
        set_module_properties("px${module_name}")
    endif()
    
    # Engine only compile definitions.
    set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
    list(APPEND MODULE_COMPILE_DEFINITIONS "PX_BUILD_${MODULE_NAME_UPPER}")
    
    target_compile_definitions(${MODULE_TARGET_NAME}
            PRIVATE
            ${MODULE_COMPILE_DEFINITIONS}
    )
endfunction()

# Excludes module from default compilation in all configurations except one.
# A module can be build anyway if hard link exists - refer generator expressions. 
function(exclude_module_from_default_build_except module enabled_config)
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
