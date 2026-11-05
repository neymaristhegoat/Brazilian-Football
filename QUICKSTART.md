# Brazilian Football - Quick Start Guide

## Installation (First Time Setup)

### Step 1: Install Dependencies

Run the automatic installer:
```bash
cd /home/neymar/Documents/Code/Brazilian-Football
chmod +x scripts/install-dependencies.sh
./scripts/install-dependencies.sh
```

This will install:
- Build tools (CMake, GCC)
- Graphics libraries (GLFW, GLEW, GLM, OpenGL)
- Python 3

**Supported distributions:**
- Ubuntu/Debian/Linux Mint/Pop!_OS
- Fedora/RHEL/CentOS
- Arch Linux/Manjaro
- openSUSE

### Step 2: Build the Project

```bash
chmod +x setup.sh
./setup.sh
```

### Step 3: Run the Demo

```bash
./bin/BrazilianFootball
```

or

```bash
./build/linux/bin/BrazilianFootball
```

## Troubleshooting

### "glfw3 not found" or "GLEW not found"

**Solution:**
```bash
./scripts/install-dependencies.sh
```

### "Permission denied" when running scripts

**Solution:**
```bash
chmod +x scripts/*.sh
chmod +x setup.sh
./setup.sh
```

### Build fails with missing headers

**Solution:** Install development packages
```bash
# Ubuntu/Debian
sudo apt-get install libglfw3-dev libglew-dev libglm-dev build-essential cmake

# Fedora
sudo dnf install glfw-devel glew-devel glm-devel gcc-c++ cmake

# Arch
sudo pacman -S glfw-x11 glew glm base-devel cmake
```

### CMake configuration fails

**Solution:** Clean and rebuild
```bash
rm -rf build
python3 scripts/compile-linux.py --clean
```

### Black screen when running

**Check OpenGL support:**
```bash
glxinfo | grep "OpenGL version"
```

Need OpenGL 4.1 or higher. Update graphics drivers if needed.

### Binary not found after build

**Check both locations:**
```bash
ls -la bin/BrazilianFootball
ls -la build/linux/bin/BrazilianFootball
```

**Manual build:**
```bash
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j$(nproc)
cd ..
./build/bin/BrazilianFootball
```

## Manual Dependency Installation

### Ubuntu/Debian/Linux Mint
```bash
sudo apt-get update
sudo apt-get install -y \
    build-essential \
    cmake \
    libglfw3-dev \
    libglew-dev \
    libglm-dev \
    libgl1-mesa-dev \
    python3
```

### Fedora/RHEL/CentOS
```bash
sudo dnf install -y \
    gcc-c++ \
    cmake \
    glfw-devel \
    glew-devel \
    glm-devel \
    mesa-libGL-devel \
    python3
```

### Arch Linux/Manjaro
```bash
sudo pacman -S --needed \
    base-devel \
    cmake \
    glfw-x11 \
    glew \
    glm \
    mesa \
    python
```

## Verification

Check if everything is installed:
```bash
./scripts/check-dependencies.sh
```

Should show all ✓ checkmarks.

## What You Should See

When running the demo:
- Window titled "Brazilian Football"
- 3D scene with:
  - Rotating cubes
  - Bouncing sphere
  - Grid of animated cubes
  - Green ground plane
  - Smooth camera movement
- ~60 FPS

**Controls:** ESC to exit

## Development

### Debug Build
```bash
python3 scripts/compile-linux.py --debug
```

### Clean Build
```bash
python3 scripts/compile-linux.py --clean
```

### Run Tests
```bash
cd build/linux
ctest --output-on-failure
```

## Getting Help

1. Check error messages carefully
2. Run dependency checker: `./scripts/check-dependencies.sh`
3. Try clean build: `python3 scripts/compile-linux.py --clean`
4. Check GPU drivers are up to date
5. Verify OpenGL 4.1+ support

## Next Steps

Once the demo runs successfully:
1. Explore the code in `engine/src/`
2. Modify the demo scene in `engine/src/demo/DemoScene.cpp`
3. Start building game features!

See `docs/ARCHITECTURE.md` for system overview.
