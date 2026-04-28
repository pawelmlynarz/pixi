@echo off

cd /d "%~dp0"

::
:: Prerequisites Check
:: 

where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo Cmake not found in path. Use setup_prereqs.bat to install prerequisites.
    pause
    exit /b 1
)

set ENGINE_ROOT=%CD%/../..

if not exist %ENGINE_ROOT%/../build  (
	cd %ENGINE_ROOT%/..
	mkdir build
	cd build
) else (
	cd %ENGINE_ROOT%/../build
)

if "%~1"=="" (
    cmake .. -G "Visual Studio 17 2022"
) else (
    cmake .. -G "Visual Studio 17 2022" -DPROJECT_NAME_OVERRIDE=%~1
)

pause
