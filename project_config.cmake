# --------------------------------------------------
# Project configuration
# --------------------------------------------------

set(BUILD_GAME OFF)
set(GAME_TARGET_NAME game)

if(BUILD_GAME)
    set(PROJECT_NAME "${GAME_TARGET_NAME}")
else()
    set(PROJECT_NAME pixi)
endif()

set(BUILD_SANDBOX ON)
set(SANDBOX_TARGET_NAME sandbox)
