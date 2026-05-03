@echo off
setlocal EnableExtensions EnableDelayedExpansion

:: ============================================================
:: Prerequisite installer/checker
:: ============================================================

set "CMAKE_MIN_VERSION=4.3"
set "CLANG_MIN_VERSION=22.1"
set "NINJA_MIN_VERSION=1.12"

call :CHECK_CMAKE
if errorlevel 1 exit /b 1

call :CHECK_CLANG
if errorlevel 1 exit /b 1

call :CHECK_NINJA
if errorlevel 1 exit /b 1

echo.
echo [32mAll prerequisites are installed and satisfy the minimum versions.[0m
pause
exit /b 0

:: ============================================================
:: CMake
:: ============================================================

:CHECK_CMAKE
echo.
echo Checking CMake...

set "CMAKE_VER="
set "CMAKE_VER_MAJOR="
set "CMAKE_VER_MINOR="
set "CMAKE_VER_PATCH="

where cmake >nul 2>&1
if errorlevel 1 (
    echo CMake is missing.
    call :INSTALL_CMAKE
    if errorlevel 1 exit /b 1
    goto CHECK_CMAKE
)

for /f "tokens=1,2,3" %%A in ('cmake --version 2^>nul') do (
    if /i "%%A %%B"=="cmake version" set "CMAKE_VER=%%C"
)

if not defined CMAKE_VER (
    echo [31mUnable to determine CMake version.[0m
    exit /b 1
)

call :PARSE_VERSION "%CMAKE_VER%" CMAKE_VER_MAJOR CMAKE_VER_MINOR CMAKE_VER_PATCH
call :PARSE_VERSION "%CMAKE_MIN_VERSION%" CMAKE_MIN_MAJOR CMAKE_MIN_MINOR CMAKE_MIN_PATCH

call :VERSION_AT_LEAST !CMAKE_VER_MAJOR! !CMAKE_VER_MINOR! !CMAKE_MIN_MAJOR! !CMAKE_MIN_MINOR!
if errorlevel 1 (
    echo CMake !CMAKE_VER! is too old. Minimum required: !CMAKE_MIN_VERSION!
    call :INSTALL_CMAKE
    if errorlevel 1 exit /b 1
    goto CHECK_CMAKE
)

echo [32mCMake found: !CMAKE_VER! ^(min. !CMAKE_MIN_VERSION!^)[0m
exit /b 0


:INSTALL_CMAKE
echo Installing CMake via winget...

winget install --id Kitware.CMake --exact --silent --accept-package-agreements --accept-source-agreements
if errorlevel 1 (
    echo [31mFailed to install CMake via winget.[0m
    echo Manual install: https://cmake.org/download/
    pause
    exit /b 1
)

where cmake >nul 2>&1
if errorlevel 1 (
    echo CMake was installed but is not available in PATH yet.
    echo Please restart your terminal and re-run this script.
    pause
    exit /b 0
)

exit /b 0

:: ============================================================
:: Clang / LLVM
:: ============================================================

:CHECK_CLANG
echo.
echo Checking Clang...

set "CLANG_VER="
set "CLANG_VER_MAJOR="
set "CLANG_VER_MINOR="
set "CLANG_VER_PATCH="

where clang >nul 2>&1
if errorlevel 1 (
    echo Clang is missing.
    call :INSTALL_CLANG
    if errorlevel 1 exit /b 1
    goto CHECK_CLANG
)

for /f "tokens=3" %%A in ('clang --version 2^>nul ^| findstr /i "version"') do (
    set "CLANG_VER=%%A"
    goto CLANG_VERSION_FOUND
)

:CLANG_VERSION_FOUND

if not defined CLANG_VER (
    echo [31mUnable to determine Clang version.[0m
    exit /b 1
)

call :PARSE_VERSION "%CLANG_VER%" CLANG_VER_MAJOR CLANG_VER_MINOR CLANG_VER_PATCH
call :PARSE_VERSION "%CLANG_MIN_VERSION%" CLANG_MIN_MAJOR CLANG_MIN_MINOR CLANG_MIN_PATCH

call :VERSION_AT_LEAST !CLANG_VER_MAJOR! !CLANG_VER_MINOR! !CLANG_MIN_MAJOR! !CLANG_MIN_MINOR!
if errorlevel 1 (
    echo Clang !CLANG_VER! is too old. Minimum required: !CLANG_MIN_VERSION!
    call :INSTALL_CLANG
    if errorlevel 1 exit /b 1
    goto CHECK_CLANG
)

echo [32mClang found: !CLANG_VER! ^(min. !CLANG_MIN_VERSION!^)[0m
exit /b 0


:INSTALL_CLANG
echo Installing Clang/LLVM via winget...

winget install --id LLVM.LLVM --exact --silent --accept-package-agreements --accept-source-agreements
if errorlevel 1 (
    echo [31mFailed to install Clang/LLVM via winget.[0m
    echo Manual install: https://releases.llvm.org/
    pause
    exit /b 1
)

where clang >nul 2>&1
if errorlevel 1 (
    echo Clang was installed but is not available in PATH yet.
    echo Please restart your terminal and re-run this script.
    pause
    exit /b 0
)

exit /b 0

:: ============================================================
:: Ninja
:: ============================================================

:CHECK_NINJA
echo.
echo Checking Ninja...

set "NINJA_VER="
set "NINJA_VER_MAJOR="
set "NINJA_VER_MINOR="
set "NINJA_VER_PATCH="

where ninja >nul 2>&1
if errorlevel 1 (
    echo Ninja is missing.
    call :INSTALL_NINJA
    if errorlevel 1 exit /b 1
    goto CHECK_NINJA
)

for /f "tokens=1" %%A in ('ninja --version 2^>nul') do (
    set "NINJA_VER=%%A"
)

if not defined NINJA_VER (
    echo [31mUnable to determine Ninja version.[0m
    exit /b 1
)

call :PARSE_VERSION "%NINJA_VER%" NINJA_VER_MAJOR NINJA_VER_MINOR NINJA_VER_PATCH
call :PARSE_VERSION "%NINJA_MIN_VERSION%" NINJA_MIN_MAJOR NINJA_MIN_MINOR NINJA_MIN_PATCH

call :VERSION_AT_LEAST !NINJA_VER_MAJOR! !NINJA_VER_MINOR! !NINJA_MIN_MAJOR! !NINJA_MIN_MINOR!
if errorlevel 1 (
    echo Ninja !NINJA_VER! is too old. Minimum required: !NINJA_MIN_VERSION!
    call :INSTALL_NINJA
    if errorlevel 1 exit /b 1
    goto CHECK_NINJA
)

echo [32mNinja found: !NINJA_VER! ^(min. !NINJA_MIN_VERSION!^)[0m
exit /b 0


:INSTALL_NINJA
echo Installing Ninja via winget...

winget install --id Ninja-build.Ninja --exact --silent --accept-package-agreements --accept-source-agreements
if errorlevel 1 (
    echo [31mFailed to install Ninja via winget.[0m
    echo Manual install: https://github.com/ninja-build/ninja/releases
    pause
    exit /b 1
)

where ninja >nul 2>&1
if errorlevel 1 (
    echo Ninja was installed but is not available in PATH yet.
    echo Please restart your terminal and re-run this script.
    pause
    exit /b 0
)

exit /b 0

r:: ============================================================
r:: Helpers
r:: ============================================================

:PARSE_VERSION
:: Usage:
::   call :PARSE_VERSION "1.2.3" MAJOR_VAR MINOR_VAR PATCH_VAR

set "VERSION_STRING=%~1"

for /f "tokens=1,2,3 delims=.-+" %%A in ("%VERSION_STRING%") do (
    set "%~2=%%A"
    set "%~3=%%B"
    set "%~4=%%C"
)

if not defined %~2 set "%~2=0"
if not defined %~3 set "%~3=0"
if not defined %~4 set "%~4=0"

exit /b 0

:VERSION_AT_LEAST
:: Usage:
::   call :VERSION_AT_LEAST CURRENT_MAJOR CURRENT_MINOR REQUIRED_MAJOR REQUIRED_MINOR
:: Returns:
::   0 when current version is greater than or equal to required version
::   1 when current version is lower than required version

set /a "CURRENT_MAJOR=%~1"
set /a "CURRENT_MINOR=%~2"
set /a "REQUIRED_MAJOR=%~3"
set /a "REQUIRED_MINOR=%~4"

if %CURRENT_MAJOR% GTR %REQUIRED_MAJOR% exit /b 0
if %CURRENT_MAJOR% LSS %REQUIRED_MAJOR% exit /b 1

if %CURRENT_MINOR% GEQ %REQUIRED_MINOR% exit /b 0

exit /b 1
