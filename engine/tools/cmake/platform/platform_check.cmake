set(HOST_PLATFORM_SUPPORTED OFF)
set(HOST_PLATFORM_WINDOWS OFF)

# Host platform check.	
if(WIN32)
    set(HOST_PLATFORM_SUPPORTED ON)
    set(HOST_PLATFORM_WINDOWS ON)
	
	set(CMAKE_SYSTEM_HOST_NAME Windows)
endif()

if(NOT HOST_PLATFORM_SUPPORTED)
    message(FATAL_ERROR
            "Unsupported host platform. Supported host platforms: Windows."
    )
endif()

if(NOT DEFINED CMAKE_SYSTEM_NAME OR CMAKE_SYSTEM_NAME STREQUAL "")
    message(FATAL_ERROR "CMAKE_SYSTEM_NAME not set, unable to establish target platform. Missing toolchain for configuration?")
endif()

set(TARGET_PLATFORM "${CMAKE_SYSTEM_NAME}")
