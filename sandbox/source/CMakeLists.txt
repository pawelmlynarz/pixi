include(utils)

file(GLOB_RECURSE SANDBOX_SOURCES *.cpp)
file(GLOB_RECURSE SANDBOX_HEADERS *.hpp)
file(GLOB_RECURSE SANDBOX_INLINES *.inl)

target_sources(${SANDBOX_TARGET_NAME} PRIVATE
		${SANDBOX_SOURCES}
		${SANDBOX_HEADERS}
		${SANDBOX_INLINES})

target_include_directories(${SANDBOX_TARGET_NAME} PRIVATE source)

group_sources_for_target(${SANDBOX_TARGET_NAME})
