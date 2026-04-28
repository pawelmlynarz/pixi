include("utils")

file(GLOB_RECURSE ENGINE_SOURCES *.cpp)
file(GLOB_RECURSE ENGINE_HEADERS *.hpp)
file(GLOB_RECURSE ENGINE_INLINES *.inl)

target_sources(${ENGINE_TARGET_NAME} PRIVATE
		${ENGINE_SOURCES}
		${ENGINE_HEADERS}
		${ENGINE_INLINES})

target_include_directories(${ENGINE_TARGET_NAME} PUBLIC source)

group_sources_for_target(${ENGINE_TARGET_NAME})
