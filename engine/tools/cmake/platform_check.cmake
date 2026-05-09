set(PLATFORM_SUPPORTED OFF)

if(WIN32)
    set(PLATFORM_SUPPORTED ON)
    set(PLATFORM_WINDOWS ON)
endif()

if(NOT PLATFORM_SUPPORTED)
    message(FATAL_ERROR
            "Unsupported platform."
            "Supported platforms: ${SUPPORTED_PLATFORMS}"
    )
endif()
 