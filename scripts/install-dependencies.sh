#!/bin/bash

# Brazilian Football - Dependency Installation Script
# Automatically detects Linux distribution and installs required packages

set -e

echo "========================================"
echo "  Installing Brazilian Football Dependencies"
echo "========================================"
echo ""

# Check if running as root
if [ "$EUID" -eq 0 ]; then 
    echo "Please don't run this script as root (without sudo)."
    echo "The script will ask for sudo password when needed."
    exit 1
fi

# Detect Linux distribution
if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
    echo "Detected OS: $NAME"
else
    echo "Cannot detect OS. Please install dependencies manually."
    exit 1
fi

echo ""
echo "Installing dependencies..."
echo ""

case $OS in
    ubuntu|debian|linuxmint|pop)
        echo "Using apt package manager..."
        sudo apt-get update
        
        echo "Installing build tools..."
        sudo apt-get install -y build-essential cmake git pkg-config
        
        echo "Installing graphics libraries..."
        sudo apt-get install -y \
            libglfw3-dev \
            libglew-dev \
            libglm-dev \
            libgl1-mesa-dev \
            libglu1-mesa-dev
        
        echo "Installing audio libraries (optional)..."
        sudo apt-get install -y libopenal-dev libsndfile1-dev || true
        
        echo "Installing Python..."
        sudo apt-get install -y python3 python3-pip
        ;;
        
    fedora|rhel|centos)
        echo "Using dnf/yum package manager..."
        
        if command -v dnf &> /dev/null; then
            PKG_MGR="dnf"
        else
            PKG_MGR="yum"
        fi
        
        echo "Installing build tools..."
        sudo $PKG_MGR install -y gcc-c++ cmake git pkgconfig
        
        echo "Installing graphics libraries..."
        sudo $PKG_MGR install -y \
            glfw-devel \
            glew-devel \
            glm-devel \
            mesa-libGL-devel \
            mesa-libGLU-devel
        
        echo "Installing audio libraries (optional)..."
        sudo $PKG_MGR install -y openal-soft-devel libsndfile-devel || true
        
        echo "Installing Python..."
        sudo $PKG_MGR install -y python3 python3-pip
        ;;
        
    arch|manjaro)
        echo "Using pacman package manager..."
        
        echo "Installing build tools..."
        sudo pacman -S --needed --noconfirm base-devel cmake git pkgconf
        
        echo "Installing graphics libraries..."
        sudo pacman -S --needed --noconfirm \
            glfw-x11 \
            glew \
            glm \
            mesa \
            glu
        
        echo "Installing audio libraries (optional)..."
        sudo pacman -S --needed --noconfirm openal libsndfile || true
        
        echo "Installing Python..."
        sudo pacman -S --needed --noconfirm python python-pip
        ;;
        
    opensuse*|suse)
        echo "Using zypper package manager..."
        
        echo "Installing build tools..."
        sudo zypper install -y gcc-c++ cmake git pkg-config
        
        echo "Installing graphics libraries..."
        sudo zypper install -y \
            glfw3-devel \
            glew-devel \
            glm-devel \
            Mesa-libGL-devel \
            glu-devel
        
        echo "Installing audio libraries (optional)..."
        sudo zypper install -y openal-soft-devel libsndfile-devel || true
        
        echo "Installing Python..."
        sudo zypper install -y python3 python3-pip
        ;;
        
    *)
        echo "Unsupported distribution: $OS"
        echo ""
        echo "Please install the following packages manually:"
        echo "  - build-essential / gcc-c++"
        echo "  - cmake (3.20+)"
        echo "  - libglfw3-dev / glfw-devel"
        echo "  - libglew-dev / glew-devel"
        echo "  - libglm-dev / glm-devel"
        echo "  - OpenGL development files"
        echo "  - Python 3"
        exit 1
        ;;
esac

echo ""
echo "========================================"
echo "✓ Dependencies installed successfully!"
echo "========================================"
echo ""
echo "Verifying installation..."
echo ""

# Verify installations
check_command() {
    if command -v $1 &> /dev/null; then
        echo "  ✓ $1 found"
        return 0
    else
        echo "  ✗ $1 not found"
        return 1
    fi
}

check_pkg_config() {
    if pkg-config --exists $1 2>/dev/null; then
        VERSION=$(pkg-config --modversion $1)
        echo "  ✓ $1 found (version $VERSION)"
        return 0
    else
        echo "  ✗ $1 not found via pkg-config"
        return 1
    fi
}

ALL_OK=true

check_command cmake || ALL_OK=false
check_command g++ || check_command clang++ || ALL_OK=false
check_command python3 || ALL_OK=false
check_pkg_config glfw3 || ALL_OK=false
check_pkg_config glew || ALL_OK=false

# Check for GLM (header-only, so just check for file)
if [ -f /usr/include/glm/glm.hpp ] || [ -f /usr/local/include/glm/glm.hpp ]; then
    echo "  ✓ GLM found"
else
    echo "  ✗ GLM headers not found"
    ALL_OK=false
fi

echo ""
if [ "$ALL_OK" = true ]; then
    echo "✓ All dependencies verified!"
    echo ""
    echo "Next steps:"
    echo "  1. Run: ./setup.sh"
    echo "  2. Run: ./bin/BrazilianFootball"
else
    echo "⚠ Some dependencies may not be properly installed."
    echo "Please check the errors above and install missing packages."
    exit 1
fi
