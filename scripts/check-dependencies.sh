#!/bin/bash

# Quick dependency checker and installer
# Run this before setup.sh if you haven't installed dependencies

set -e

echo "Checking for Brazilian Football dependencies..."
echo ""

MISSING=()

# Check CMake
if ! command -v cmake &> /dev/null; then
    echo "✗ CMake not found"
    MISSING+=("cmake")
else
    echo "✓ CMake found"
fi

# Check compiler
if ! command -v g++ &> /dev/null && ! command -v clang++ &> /dev/null; then
    echo "✗ C++ compiler not found"
    MISSING+=("compiler")
else
    echo "✓ C++ compiler found"
fi

# Check pkg-config
if ! command -v pkg-config &> /dev/null; then
    echo "✗ pkg-config not found"
    MISSING+=("pkg-config")
else
    echo "✓ pkg-config found"
fi

# Check GLFW
if pkg-config --exists glfw3 2>/dev/null; then
    echo "✓ GLFW found"
else
    echo "✗ GLFW not found"
    MISSING+=("glfw")
fi

# Check GLEW
if pkg-config --exists glew 2>/dev/null; then
    echo "✓ GLEW found"
else
    echo "✗ GLEW not found"
    MISSING+=("glew")
fi

# Check GLM
if [ -f /usr/include/glm/glm.hpp ] || [ -f /usr/local/include/glm/glm.hpp ]; then
    echo "✓ GLM found"
else
    echo "✗ GLM not found"
    MISSING+=("glm")
fi

echo ""

if [ ${#MISSING[@]} -eq 0 ]; then
    echo "=========================================="
    echo "✓ All dependencies are installed!"
    echo "=========================================="
    echo ""
    echo "Ready to build. Run:"
    echo "  ./setup.sh"
    exit 0
else
    echo "=========================================="
    echo "Missing dependencies detected"
    echo "=========================================="
    echo ""
    echo "Missing: ${MISSING[*]}"
    echo ""
    echo "To install all dependencies automatically, run:"
    echo "  ./scripts/install-dependencies.sh"
    echo ""
    echo "Or install manually:"
    
    if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        echo "  sudo apt-get install libglfw3-dev libglew-dev libglm-dev cmake build-essential"
    elif [[ "$OSTYPE" == "darwin"* ]]; then
        echo "  brew install glfw glew glm cmake"
    fi
    
    exit 1
fi
