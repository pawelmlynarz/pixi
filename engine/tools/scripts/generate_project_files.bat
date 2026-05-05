:: --------------------------------------------------
:: Script: generate_project_files.bat
::
:: Description:
::   Generates project files using any supported generator.
::
:: Usage:
::   generate_project_files.bat <GENERATOR_NAME>
::
:: --------------------------------------------------

@echo off

:: --------------------------------------------------
:: Args Check
:: --------------------------------------------------

if "%~1"=="" goto FAIL_INVALID_ARGS
set "GENERATOR=%~1"

:: --------------------------------------------------
:: Prerequisites Check
:: --------------------------------------------------

where cmake >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [31mCmake not found in PATH.[0m
    goto FAIL_INVALID_PREREQS
)

where clang >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo [31mClang not found in PATH.[0m
    goto FAIL_INVALID_PREREQS
)

cd /d "%~dp0"

set ENGINE_ROOT=%CD%/../..

if not exist %ENGINE_ROOT%/../build  (
	cd %ENGINE_ROOT%/..
	mkdir build
	cd build
) else (
	cd %ENGINE_ROOT%/../build
)

::
:: Project Generation
:: 

echo Generating project files..

cmake .. -G "%GENERATOR%"
if %ERRORLEVEL% NEQ 0 goto FAIL_PROJECT_GENERATION

echo [32mSuccessfully generated project files.[0m
pause
exit /b 0

:FAIL_INVALID_ARGS
echo [31mError: Invalid arguments.[0m
echo Usage: %~nx0 GENERATOR_NAME
pause
exit /b 1

:FAIL_INVALID_PREREQS
echo [31mError: Prerequisites not met. Use setup_prereqs.bat to install prerequisites.[0m
pause
exit /b 1

:FAIL_PROJECT_GENERATION
echo [31mError: Failed to generate project files.[0m
pause
exit /b 1
