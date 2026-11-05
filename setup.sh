#!/bin/bash

# Brazilian Football - Quick Start Script
# Sets up the development environment and builds the project

set -e  # Exit on error

echo "Brazilian Football - Development Setup"
echo "======================================"

# Check for required tools
echo "Checking dependencies..."

command -v cmake >/dev/null 2>&1 || { echo "CMake is required but not installed. Aborting." >&2; exit 1; }
command -v python3 >/dev/null 2>&1 || { echo "Python 3 is required but not installed. Aborting." >&2; exit 1; }

echo "✓ All required tools found"

# Create necessary directories
echo "Creating directory structure..."
mkdir -p build
mkdir -p bin
mkdir -p assets/models
mkdir -p assets/textures
mkdir -p assets/audio/music
mkdir -p assets/audio/sfx
mkdir -p external/include
mkdir -p external/lib

echo "✓ Directories created"

# Build the project
echo "Building project..."
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    python3 scripts/compile-linux.py --debug
elif [[ "$OSTYPE" == "darwin"* ]]; then
    python3 scripts/compile-mac.py --debug
else
    echo "Unsupported OS. Please build manually."
    exit 1
fi

echo ""
echo "======================================"
echo "Setup complete!"
echo ""
echo "To run the game:"
echo "  ./bin/BrazilianFootball"
echo ""
echo "To run tests:"
echo "  cd build && ctest"
echo ""
echo "For more information, see docs/"
