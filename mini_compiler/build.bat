@echo off
echo Building and running the mini compiler...
echo.

REM Compile the C++ compiler
echo Compiling mini_compiler...
g++ -std=c++17 -Wall -Wextra -o mini_compiler code.cpp
if %ERRORLEVEL% NEQ 0 (
    echo Failed to compile mini_compiler!
    pause
    exit /b 1
)

REM Run the compiler to generate assembly
echo.
echo Running mini_compiler to generate assembly...
mini_compiler
if %ERRORLEVEL% NEQ 0 (
    echo Failed to generate assembly!
    pause
    exit /b 1
)

REM Assemble the generated code
echo.
echo Assembling output.asm...
nasm -f win32 output.asm -o output.obj
if %ERRORLEVEL% NEQ 0 (
    echo Failed to assemble output.asm!
    pause
    exit /b 1
)

REM Link the object file
echo.
echo Linking output.obj...
gcc -m32 output.obj -o program.exe
if %ERRORLEVEL% NEQ 0 (
    echo Failed to link output.obj!
    pause
    exit /b 1
)

REM Run the final program
echo.
echo Running the program...
echo ----------------------
program.exe
echo ----------------------

echo.
echo All steps completed successfully!
pause 