@echo off
setlocal enabledelayedexpansion

::
:: CMake
:: 

:CMAKE_CHECK

set CMAKE_MIN_VERSION=4.3

where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Cmake not found in path.
    goto CMAKE_INSTALL
)

for /f "tokens=1,2,3" %%A in ('cmake --version 2^>nul') do (
    if /i "%%A %%B"=="cmake version" set CMAKE_VER=%%C
)

for /f "tokens=1,2,3 delims=." %%A in ("!CMAKE_VER!") do (
    set CMAKE_VER_MAJOR=%%A
    set CMAKE_VER_MINOR=%%B
    set CMAKE_VER_PATCH=%%C
)
for /f "tokens=1,2 delims=." %%A in ("!CMAKE_MIN_VERSION!") do (
    set CMAKE_MIN_MAJOR=%%A
    set CMAKE_MIN_MINOR=%%B
)

if !CMAKE_VER_MAJOR! GTR !CMAKE_MIN_MAJOR! goto CMAKE_SUCCESS
if !CMAKE_VER_MAJOR! EQU !CMAKE_MIN_MAJOR! (
    if !CMAKE_VER_MINOR! GEQ !CMAKE_MIN_MINOR! goto CMAKE_SUCCESS
)

echo CMake !CMAKE_VER! is too old. Minimum required: !CMAKE_MIN_VERSION!
goto CMAKE_INSTALL

:CMAKE_INSTALL

echo Installing CMake via winget...
winget install Kitware.CMake --silent
if %ERRORLEVEL% NEQ 0 (
    echo Failed to install Cmake via winget. Try manual install from https://cmake.org/download/.
    pause
    exit /b 1
)

for /f "tokens=*" %%P in ('where cmake 2^>nul') do set CMAKE_PATH=%%P
if "!CMAKE_PATH!"=="" (
    echo CMake installed but not found in PATH yet.
    echo Please restart your terminal and re-run this script.
    pause
    exit /b 0
)
goto CMAKE_CHECK

:CMAKE_SUCCESS

echo CMake: %CMAKE_VER_MAJOR%.%CMAKE_VER_MINOR%.%CMAKE_VER_PATCH% (min. %CMAKE_MIN_MAJOR%.%CMAKE_MIN_MINOR%)
pause
exit /b 0