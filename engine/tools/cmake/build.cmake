# Excludes module from default compilation in all configurations except one.
# A module can be build anyway if hard link exists - refer generator expressions. 
function(exclude_target_from_default_build_except target enabled_config)
    foreach(config ${CMAKE_CONFIGURATION_TYPES})
        string(TOUPPER "${config}" config_upper)

        if("${config}" STREQUAL "${enabled_config}")
            set(exclude FALSE)
        else()
            set(exclude TRUE)
        endif()

        set_target_properties(${target} PROPERTIES
                EXCLUDE_FROM_DEFAULT_BUILD_${config_upper} ${exclude}
        )
    endforeach()
endfunction()
