# Mini Compiler

A simple compiler that demonstrates basic compilation concepts, including lexing, parsing, and code generation. This compiler supports a minimal language with basic arithmetic operations and a custom square operation.

## Cross-Platform Support

This compiler now supports both Windows and macOS (including Apple Silicon/ARM64 Macs)!

## Windows Quick Start

The easiest way to get started on Windows is to run the automatic installation script:

```bash
.\install_requirements.bat
```

This script will:
1. Download and install NASM
2. Download and install MinGW-w64
3. Set up the PATH environment variables
4. Verify the installations

After running the script, restart your terminal and you're ready to go!

## macOS Quick Start

To run the compiler on macOS (both Intel and Apple Silicon):

```bash
# Make the build script executable
chmod +x build.sh

# Run the compiler
./build.sh
```

The script will:
1. Detect your Mac's architecture (Intel or ARM64)
2. Compile the C++ compiler with appropriate flags
3. Generate and run code for your specific architecture
4. Show the result (square of 5)

### macOS Prerequisites

1. **Xcode Command Line Tools**
   - Install by running: `xcode-select --install`

2. **NASM (for Intel Macs only)**
   - Install with Homebrew: `brew install nasm`

3. **GCC/Clang**
   - Already included with Xcode Command Line Tools

## Manual Installation (Windows)

If you prefer to install the tools manually on Windows:

### Windows Prerequisites

1. **NASM (Netwide Assembler)**
   - Download from: https://www.nasm.us/pub/nasm/releasebuilds/2.16.01/
   - Extract to: `C:\nasm`
   - Add to PATH: `C:\nasm`

2. **MinGW-w64 (GCC for Windows)**
   - Download from: https://github.com/niXman/mingw-builds-binaries/releases
   - Extract to: `C:\mingw64`
   - Add to PATH: `C:\mingw64\bin`

### Setting Up Windows Environment

After installing the prerequisites, run:
```bash
.\setup_path.bat
```

This script will:
- Verify NASM installation
- Verify GCC installation
- Help you add them to PATH if needed

## Building and Running

### On Windows

```bash
.\build.bat
```

### On macOS

```bash
./build.sh
```

## Architecture-Specific Implementation

The compiler automatically detects your system architecture and uses the appropriate approach:

- **x86/x64 (Windows/Intel Mac)**: Generates x86 assembly with NASM
- **ARM64 (Apple Silicon Mac)**: Uses a direct C implementation for compatibility

## Example Usage

The compiler supports simple expressions like:
```
x = 5 square
```

This will:
1. Parse the expression
2. Generate architecture-appropriate code
3. Compile and run the code
4. Output: `Result: 25`

## Generated Assembly Code (x86)

On x86 platforms, the compiler generates assembly code with a custom square macro:

```nasm
; Square operation macro
%macro square 1
    ; Save operand
    mov ebx, %1
    ; Square the value
    imul %1, ebx
%endmacro
```

## Troubleshooting

### Windows Issues

1. **"Command not found" errors**
   - Run `.\setup_path.bat` to verify PATH settings
   - Restart your terminal after installation

2. **NASM/GCC not found**
   - Verify installations using `nasm --version` and `gcc --version`
   - Run `.\install_requirements.bat` to reinstall if needed

### macOS Issues

1. **Permission denied when running build.sh**
   - Run `chmod +x build.sh` to make the script executable

2. **Assembler errors on Intel Mac**
   - Ensure NASM is installed: `brew install nasm`

3. **ARM64 specific issues**
   - Make sure Xcode Command Line Tools are installed

## Project Structure

- `compiler.cpp` - Main compiler implementation
- `build.sh` - macOS build and run script
- `build.bat` - Windows build and run script
- `setup_path.bat` - Windows environment setup script
- `install_requirements.bat` - Windows automatic installation script
- `output.asm` - Generated assembly code
- `program` (macOS) / `program.exe` (Windows) - Final executable

## License

This project is open source under the MIT License.
