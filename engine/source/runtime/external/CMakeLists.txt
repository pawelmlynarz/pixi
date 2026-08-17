# --------------------------------------------------
# Component:        External
# --------------------------------------------------
# Vendored third party sources that are compiled directly into the engine.
# Headers are included as "<library>/<header>", e.g. "wyhash/wyhash.h".

include(utils)
include(build)

set(COMPONENT_NAME external)

#
# Common Sources
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        *.c *.cpp *.h *.hpp *.inl
)
target_sources(${ENGINE_TARGET_NAME} PRIVATE ${MODULE_SOURCES})
