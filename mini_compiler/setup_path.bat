@echo off
echo Setting up PATH for NASM and MinGW...

REM Check if NASM exists
where nasm > nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo NASM not found! Please enter the path where you extracted NASM:
    echo Example: C:\nasm
    set /p NASM_PATH=NASM Path: 
    setx PATH "%PATH%;%NASM_PATH%"
)

REM Check if MinGW exists
where gcc > nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    echo MinGW not found! Please enter the path to MinGW's bin directory:
    echo Example: C:\mingw64\bin
    set /p MINGW_PATH=MinGW Path: 
    setx PATH "%PATH%;%MINGW_PATH%"
)

echo.
echo Checking installations...
echo.

echo Testing NASM...
nasm -v
if %ERRORLEVEL% NEQ 0 (
    echo NASM is not properly installed or not in PATH
) else (
    echo NASM is properly installed
)

echo.
echo Testing GCC...
gcc --version
if %ERRORLEVEL% NEQ 0 (
    echo GCC is not properly installed or not in PATH
) else (
    echo GCC is properly installed
)

echo.
echo If both tools are properly installed, you can now run build.bat
pause 