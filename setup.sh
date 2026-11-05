#!/bin/bash

# Brazilian Football - Enhanced Setup Script
# Checks dependencies first, then builds

set -e

echo "======================================"
echo "Brazilian Football - Development Setup"
echo "======================================"
echo ""

# Check if dependencies are installed
echo "[1/5] Checking dependencies..."
echo ""

if [ -x "scripts/check-dependencies.sh" ]; then
    ./scripts/check-dependencies.sh
    if [ $? -ne 0 ]; then
        echo ""
        echo "Dependencies are missing. Install them first:"
        echo "  ./scripts/install-dependencies.sh"
        exit 1
    fi
else
    echo "⚠ Dependency checker not found, proceeding anyway..."
fi

echo ""
echo "[2/5] Creating directory structure..."
mkdir -p build
mkdir -p bin
mkdir -p assets/models
mkdir -p assets/textures
mkdir -p assets/audio/music
mkdir -p assets/audio/sfx
mkdir -p external/include
mkdir -p external/lib

echo "✓ Directories created"

echo ""
echo "[3/5] Verifying shader files..."
if [ -f "assets/shaders/basic.vert" ] && [ -f "assets/shaders/basic.frag" ]; then
    echo "✓ Shaders found"
else
    echo "⚠ Shader files missing (will be created during build)"
fi

echo ""
echo "[4/5] Building project..."
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    python3 scripts/compile-linux.py $@
elif [[ "$OSTYPE" == "darwin"* ]]; then
    python3 scripts/compile-mac.py $@
else
    echo "Unsupported OS for automatic build."
    echo "Please build manually with CMake."
    exit 1
fi

echo ""
echo "[5/5] Verifying build..."

if [ -f "bin/BrazilianFootball" ] || [ -f "build/linux/bin/BrazilianFootball" ]; then
    echo "✓ Executable built successfully"
    
    # Find the binary location
    if [ -f "bin/BrazilianFootball" ]; then
        BINARY="./bin/BrazilianFootball"
    else
        BINARY="./build/linux/bin/BrazilianFootball"
    fi
    
    echo ""
    echo "======================================"
    echo "✓ Build complete!"
    echo "======================================"
    echo ""
    echo "Graphics Demo Ready!"
    echo ""
    echo "To run the demo:"
    echo "  $BINARY"
    echo ""
    echo "You should see:"
    echo "  • Animated 3D scene"
    echo "  • Rotating cubes and bouncing sphere"
    echo "  • Orbiting camera"
    echo "  • Real-time lighting"
    echo ""
    echo "Controls: ESC to exit"
    echo ""
else
    echo "⚠ Executable not found"
    echo ""
    echo "Build may have completed but binary is in unexpected location."
    echo "Check the build output above for errors."
fi
