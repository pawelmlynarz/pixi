# --------------------------------------------------
# Project configuration
# --------------------------------------------------

# Set to true to build game project.
set(BUILD_GAME OFF)

# Name of the game project.
set(GAME_TARGET_NAME game)

if(BUILD_GAME)
    set(PROJECT_NAME "${GAME_TARGET_NAME}")
else()
    set(PROJECT_NAME pixi)
endif()

# Set to true to build sandbox showcase project.
set(BUILD_SANDBOX ON)
