# t-x64-msvc.cmake

set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER cl)
set(CMAKE_CXX_COMPILER cl)

# Ensure we use MSVC ABI
set(CMAKE_CXX_COMPILER_ID MSVC)

# Enforce runtime selection consistency (MD/MDd)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL")

# Disable GNU-like assumptions
set(CMAKE_C_COMPILER_FRONTEND_VARIANT "MSVC")
set(CMAKE_CXX_COMPILER_FRONTEND_VARIANT "MSVC")
