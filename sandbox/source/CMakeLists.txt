include(utils)
                                  
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
		*.cpp *.h *.inl
)

target_sources(${SANDBOX_TARGET_NAME} PRIVATE ${MODULE_SOURCES})

target_include_directories(${SANDBOX_TARGET_NAME} PRIVATE source)

group_sources_for_target(${MODULE_SOURCES})
