@echo off
setlocal enabledelayedexpansion

REM Check if the base directory is provided as an argument
if "%~1"=="" (
    echo Usage: %~nx0 ^<base-examples-directory^>
    exit /b 1
)

REM Get the base directory from the first argument
set "SEARCH_DIR=%~1"

REM Check if the directory exists
if not exist "%SEARCH_DIR%" (
    echo Directory does not exist.
    exit /b 1
)

REM Initialize an array to hold directory names
set "directories="

REM Iterate over directories in the base directory
for /d %%D in ("%SEARCH_DIR%\*") do (
    set "dirName=%%~nxD"
	echo !dirName! | findstr /i "find_package" >nul
    if errorlevel 1 (
        REM Add the directory to the array if it does not contain "modules"
        set "directories=!directories! %%D"
    )
)

REM Check if the array is not empty
if "%directories%"=="" (
    echo No directories found.
) else (
    REM Iterate over the array and print each directory name
    for %%D in (%directories%) do (
        echo Configuring the %%D example
		cmake -G "Visual Studio 17 2022" -S %%D -B %%D-build
		echo Building the %%D example
		cmake --build %%D-build
    )
)

endlocal