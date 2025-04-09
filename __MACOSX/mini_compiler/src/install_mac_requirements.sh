#!/bin/bash

echo "====================================================="
echo "    Mini Compiler - macOS Prerequisites Installer    "
echo "====================================================="
echo ""

# Detect architecture
ARCH=$(uname -m)
echo "Detected architecture: $ARCH"
echo ""

# Check if Xcode Command Line Tools are installed
if ! command -v xcode-select &> /dev/null; then
    echo "Xcode Command Line Tools not found!"
    echo "Installing Xcode Command Line Tools..."
    xcode-select --install
    echo "Please wait until Xcode Command Line Tools installation completes, then run this script again."
    exit 1
else
    echo "✅ Xcode Command Line Tools are installed."
fi

# Check if Homebrew is installed
if ! command -v brew &> /dev/null; then
    echo "Homebrew not found! Installing Homebrew..."
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    
    # Add Homebrew to PATH
    if [[ "$ARCH" == "arm64" ]]; then
        echo 'eval "$(/opt/homebrew/bin/brew shellenv)"' >> ~/.zprofile
        eval "$(/opt/homebrew/bin/brew shellenv)"
    else
        echo 'eval "$(/usr/local/bin/brew shellenv)"' >> ~/.zprofile
        eval "$(/usr/local/bin/brew shellenv)"
    fi
    
    echo "✅ Homebrew has been installed."
else
    echo "✅ Homebrew is already installed."
fi

# Install/check NASM (mainly for Intel Macs)
if [[ "$ARCH" != "arm64" ]]; then
    if ! command -v nasm &> /dev/null; then
        echo "Installing NASM (Netwide Assembler)..."
        brew install nasm
        echo "✅ NASM has been installed."
    else
        echo "✅ NASM is already installed."
        nasm --version
    fi
else
    echo "🔍 Apple Silicon Mac detected - NASM is not required for ARM64."
fi

# Check for GCC installation
if ! command -v gcc &> /dev/null; then
    echo "Installing GCC..."
    brew install gcc
    echo "✅ GCC has been installed."
else
    echo "✅ GCC is already installed."
    gcc --version
fi

echo ""
echo "====================================================="
echo "    All prerequisites have been installed!           "
echo "====================================================="
echo ""
echo "You can now run the mini compiler with:"
echo "./build.sh"
echo ""
echo "Don't forget to make the script executable first:"
echo "chmod +x build.sh"
echo ""
