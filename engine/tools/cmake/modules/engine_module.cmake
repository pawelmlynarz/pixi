function(set_engine_module_properties module_name)
    string(TOUPPER "${module_name}" MODULE_NAME_UPPER)

    # Compile definitions.
    set(MODULE_COMPILE_DEFINITIONS ${PX_ENGINE_COMPILE_DEFINITIONS})
    list(APPEND MODULE_COMPILE_DEFINITIONS "PX_BUILD_${MODULE_NAME_UPPER}")
    target_compile_definitions(${MODULE_TARGET_NAME} 
            PRIVATE 
            ${MODULE_COMPILE_DEFINITIONS}
            PUBLIC
            WITH_EDITOR=$<IF:$<CONFIG:DebugEditor>,1,0>
            WITH_IMGUI=$<IF:$<CONFIG:DebugEditor>,1,0>
    )
    
    # Compile options.
    target_compile_options(${MODULE_TARGET_NAME} PRIVATE ${GLOB_COMPILE_OPTIONS})
endfunction()
